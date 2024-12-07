#include "EnemyWalk.h"

void EnemyWalk::Initialize()
{
	auto& transform = gameObjectManager_->GetObj3dData(INameable::name_)->GetWorldTransform().transform;
	SetObjectData(transform);

	Math::Vector::Vector2 minmax = { -1.0f,1.0f };
	aabb_ = { Math::Vector::Multiply(transform.scale,minmax.x), Math::Vector::Multiply(transform.scale,minmax.y) };
	isExtrusion_ = true;
	id_ = kEnemyWalkId;
	attribute_ = CollisionMask::kEnemyWalkAttribute;
	mask_ = CollisionMask::kEnemyWalkMask;

	state_ = make_unique<EnemyWalkStateMove>();
	state_->Initialize(this);
	velocity_.x = 0.1f;
}

void EnemyWalk::Update()
{
	state_->Update(this);

	auto& transform = GameObjectManager::GetInstance()->GetObj3dData(INameable::name_)->GetWorldTransform().transform;
	transform.translate.x += velocity_.x;
	transform.translate.y += velocity_.y;

	ClearExtrusion();
	ClearHitDirection();
	isHit_ = false;
}

void EnemyWalk::OnCollision(ICollider* c, [[maybe_unused]]IObjectData* objData)
{
	isHit_ = true;

	{//敵同士の処理
		if (kEnemyWalkId == c->GetId())
		{
			velocity_.x *= 1.0f;
		}
	}

	{//プレイヤーとの処理
		if (kPlayerBullet == c->GetId())
		{
			if (!isDead_)
			{
				impactDirection_ = objData->GetVelocity();
				isDead_ = true;
				gameObjectManager_->SetObjectPipline(make_unique<Phong3dDissolvePipline>(), INameable::name_);
				ChangeState(make_unique<EnemyWalkStateDead>());
			}
		}

		if (kPlayerId == c->GetId())
		{
			if (!isDead_)
			{
				isDead_ = true;
				gameObjectManager_->SetObjectPipline(make_unique<Phong3dDissolvePipline>(), INameable::name_);
				ChangeState(make_unique<EnemyWalkStateDead>());
			}
		}
	}

	//ブロックとの処理
	if (kNormalBlock == c->GetId()) {
		for (auto& hitDirection : hitDirection_)
		{
			if (hitDirection == TOP)
			{
				velocity_.y = 0.0f;;
			}
			if (hitDirection == BOTTOM && velocity_.y <= 0.0f)
			{
				velocity_ .y=0.0f;
			}
			if (hitDirection == LEFT || hitDirection == RIGHT)
			{
				velocity_.x *= -1.0f;
			}
		}
		auto& transform = gameObjectManager_->GetObj3dData(INameable::name_)->GetWorldTransform().transform;
		transform.translate.x += extrusion_.x;
		transform.translate.y += extrusion_.y;
	}
}

void EnemyWalk::ChangeState(unique_ptr<IEnemyWalkState> state)
{
	state_.release();
	state_ = move(state);
	state_->Initialize(this);
}
