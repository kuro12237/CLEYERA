#include "GunEnemy.h"

void GunEnemy::Initialize()
{
	auto& transform = gameObjectManager_->GetObj3dData(INameable::name_)->GetWorldTransform().transform;
	SetObjectData(transform);

	Math::Vector::Vector2 minmax = { -1.0f,1.0f };
	aabb_ = { Math::Vector::Multiply(transform.scale,minmax.x), Math::Vector::Multiply(transform.scale,minmax.y) };
	isExtrusion_ = true;
	id_ = kEnemyWalkId;
	attribute_ = CollisionMask::kEnemyWalkAttribute;
	mask_ = CollisionMask::kEnemyWalkMask;

	ChangeState(make_unique<GunEnemyStateMove>());

	modelHandle_ = Engine::Manager::ModelManager::LoadObjectFile("PlayerNormalBullet");
}

void GunEnemy::Update()
{
	for (size_t index = 0; index < bullets_.size(); ++index)
	{
		if (!bullets_[index])
		{
			continue;
		}
		if (bullets_[index]->GetIsDead())
		{
			bullets_[index]->INameable::GetName();
			deadBulletIndex_.push(uint32_t(index));
			GameObjectManager::GetInstance()->ClearObj3dData(bullets_[index]->INameable::GetName());
			bullets_[index].reset();
		}
	}

	if (state_)
	{
		state_->Update(this);
	}
	for (shared_ptr<GunEnemyBullet>& b : bullets_)
	{
		if (b)
		{
			b->Update();
		}
	}

	ClearExtrusion();
	ClearHitDirection();
	IsHit_ = false;
}

void GunEnemy::OnCollision(ICollider* c, IObjectData* objData)
{
	objData;
	IsHit_ = true;

	{//敵同士の処理
		if (kEnemyWalkId == c->GetId())
		{
			return;
		}
	}

	{//プレイヤーとの処理
		if (kPlayerBullet == c->GetId())
		{
			if (!isDead_)
			{
				isDead_ = true;
				gameObjectManager_->SetObjectPipline(make_unique<Phong3dDissolvePipline>(), INameable::name_);
		
			}
		}

		if (kPlayerId == c->GetId())
		{
			if (!isDead_)
			{
				isDead_ = true;
				gameObjectManager_->SetObjectPipline(make_unique<Phong3dDissolvePipline>(), INameable::name_);

			}
		}
	}

	//ブロックとの処理
	if (kNormalBlock == c->GetId()) {
		for (auto& hitDirection : hitDirection_)
		{
			if (hitDirection == TOP)
			{
				velocity_ = {};
			}
			if (hitDirection == BOTTOM && velocity_.y <= 0.0f)
			{
				velocity_ = {};
			}
			if (hitDirection == LEFT || hitDirection == RIGHT)
			{
				speed_ *= -1.0f;
			}
		}
		auto& transform = gameObjectManager_->GetObj3dData(INameable::name_)->GetWorldTransform().transform;
		transform.translate.x += extrusion_.x;
		transform.translate.y += extrusion_.y;
	}

}

void GunEnemy::ChangeState(unique_ptr<IGunEnemyState> state)
{
	state_ = move(state);

	state_->Initialize(this);
	state_->Update(this);

}

void GunEnemy::CreateBullet(const Math::Vector::Vector3& Pos)
{
	//オブジェクトの作成
	shared_ptr<Game3dObjectData> data = make_shared<Game3dObjectData>();
	data->SetObjectType("MESH");

	Engine::Transform::TransformEular transform = { {1.0f,1.0f,1.0f},{},Pos };
	data->Initialize(transform, {}, modelHandle_);

	shared_ptr<GunEnemyBullet> b = make_shared<GunEnemyBullet>();
	string name = this->INameable::name_;
	
	const float kspeed = 0.3f;
	if (speed_>0.0f)
	{
		b->SetVelocity({ kspeed,0.0f,0.0f });
	}
	else
	{
		b->SetVelocity({-kspeed,0.0f,0.0f });
	}


	//使っていない弾の配列がある時再利用
	if (!deadBulletIndex_.empty())
	{
		uint32_t newBulletIndex = deadBulletIndex_.front();
		string name_num = name + to_string(newBulletIndex);
		data->SetObjName(name_num);
		GameObjectManager::GetInstance()->PushObj3dData(data, name_num);
		b->INameable::SetName(name_num);
		bullets_[newBulletIndex] = move(b);
		deadBulletIndex_.pop();
	}
	else
	{
		//新しいindexをとリ弾にセット
		int size = int(bullets_.size());
		string name_num = name + to_string(size);
		data->SetObjName(name_num);
		GameObjectManager::GetInstance()->PushObj3dData(data, name_num);
		b->INameable::SetName(name_num);
		b->Initialize();
		bullets_.push_back(move(b));
	}

}
