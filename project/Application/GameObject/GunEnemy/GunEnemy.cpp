#include "GunEnemy.h"

void GunEnemy::Initialize()
{
	
	//dataをセット
	objectData_ = gameObjectManager_->GetObj3dData(INameable::name_);

	//コライダーセット
	this->SetColliderParamData();
	collider_->SetId(ObjectId::kGunEnemyId);
	collider_->SetIsExtrusion(true);
	collider_->SetMask(CollisionMask::kEnemyWalkMask);
	collider_->SetAttribute(CollisionMask::kEnemyWalkAttribute);

	ChangeState(make_unique<GunEnemyStateMove>());

	modelHandle_ = Engine::Manager::ModelManager::LoadObjectFile("PlayerNormalBullet");
}

void GunEnemy::Update()
{
#ifdef _USE_IMGUI

	if (ImGui::TreeNode("ebullet"))
	{
		ImGui::Text("size::%d", int(bullets_.size()));
		ImGui::TreePop();
	}
#endif // _USE_IMGUI

	if (isEnd_)
	{
		collider_->SetId(ObjectId::kOnlyCollideWithBlocksid);
	}

	for (size_t index = 0; index < bullets_.size(); index++)
	{
		if (!bullets_[index])
		{
			continue;
		}
		if (bullets_[index]->GetIsDead())
		{
			gameObjectManager_->ClearObj3dData(bullets_[index]->INameable::GetName());
			bullets_[index].reset();
		}
	}

	if (state_)
	{
		state_->Update(this);
	}


	auto& transform = objectData_.lock()->GetWorldTransform().transform;
	transform.translate.x += velocity_.x;
	transform.translate.y += velocity_.y;

	if (isShot_)
	{
		CreateBullet(transform.translate);
		isShot_ = false;
	}
	for (shared_ptr<GunEnemyBullet>& b : bullets_)
	{
		if (b)
		{
			b->Update();
		}
	}

	collider_->ClearExtrusion();
	collider_->ClearHitDirection();
	IsHit_ = false;
}

void GunEnemy::OnCollision(ObjectComponent* objData)
{
	IsHit_ = true;
	auto c = objData->GetCollider();
	{//敵同士の処理
		if (ObjectId::kEnemyWalkId == c->GetId())
		{
			return;
		}
	}

	{//プレイヤーとの処理
		if (ObjectId::kPlayerBullet == c->GetId())
		{
			if (!isEnd_)
			{
				isEnd_ = true;
				gameObjectManager_->SetObjectPipline(make_unique<Phong3dDissolvePipline>(), INameable::name_);
				ChangeState(make_unique<GunEnemyStateDeadAnimation>());
			}
		}

		if (ObjectId::kPlayerId == c->GetId())
		{
			if (!isEnd_)
			{
				isEnd_ = true;
				gameObjectManager_->SetObjectPipline(make_unique<Phong3dDissolvePipline>(), INameable::name_);
				ChangeState(make_unique<GunEnemyStateDeadAnimation>());
			}
		}
	}

	//ブロックとの処理
	if (ObjectId::kNormalBlock == c->GetId()) {
		for (auto& hitDirection : collider_->GetHItDirection())
		{
			if (hitDirection == TOP)
			{
				velocity_.y = 0.0f;
			}
			if (hitDirection == BOTTOM && velocity_.y <= 0.0f)
			{
				velocity_.y = 0.0f;
			}
			if (hitDirection == LEFT || hitDirection == RIGHT)
			{
				velocity_.x *= -1.0f;
			}
		}
		auto& transform = objectData_.lock()->GetWorldTransform().transform;

		transform.translate.x += collider_->GetExtrusion().x;
		transform.translate.y += collider_->GetExtrusion().y;
	}

}


void GunEnemy::CreateBullet(const Math::Vector::Vector3& Pos)
{
	//オブジェクトの作成
	shared_ptr<Game3dObjectData> data = make_shared<Game3dObjectData>();
	data->SetObjectType("MESH");

	const Engine::Transform::TransformEular transform = { {1.0f,1.0f,1.0f},{},Pos };
	data->Initialize(transform, {}, modelHandle_);

	shared_ptr<GunEnemyBullet> b = make_shared<GunEnemyBullet>();
	string name = "";
	name = "GunEnemy" + FormatNumberWithDots(enemyNumber_) + string("Bullet");

	const float kspeed = 0.4f;
	if (velocity_.x > 0.0f)
	{
		b->SetVelocity({ kspeed,0.0f,0.0f });
	}
	else
	{
		b->SetVelocity({ -kspeed,0.0f,0.0f });
	}

	//新しいindexをとリ弾にセット
	int size = int(bullets_.size());
	string name_num = name + to_string(size);
	data->SetObjName(name_num);
	GameObjectManager::GetInstance()->PushObj3dData(data, name_num);
	b->INameable::SetName(name_num);
	b->Initialize();
	bullets_.push_back(move(b));
}
