#include "GunEnemyPart.h"

void GunEnemyPart::Initialize()
{
	auto& transform = gameObjectManager_->GetObj3dData(INameable::name_)->GetWorldTransform().transform;
	SetObjectData(transform);

	const Math::Vector::Vector2 minmax = { -1.0f,1.0f };
	aabb_ = { Math::Vector::Multiply(transform.scale,minmax.x), Math::Vector::Multiply(transform.scale,minmax.y) };
	isExtrusion_ = true;
	id_ = kGunEnemyId;
	attribute_ = CollisionMask::kEnemyWalkAttribute;
	mask_ = CollisionMask::kEnemyWalkMask;
}

void GunEnemyPart::Update()
{
	if (*isCoreEnd_ && !isEnd_)
	{
		id_ = kOnlyCollideWithBlocksid;
		ChangeState(make_unique<GunEnemyStateDeadAnimation>());
		isEnd_ = *isCoreEnd_;
	}

	if (state_)
	{
		state_->Update(this);
	}
	auto& transform = gameObjectManager_->GetObj3dData(INameable::name_)->GetWorldTransform().transform;
	transform.translate.x += velocity_.x;
	transform.translate.y += velocity_.y;
}

void GunEnemyPart::OnCollision(ICollider* c, [[maybe_unused]] IObjectData* objData)
{
	IsHit_ = true;

	//ブロックとの処理
	if (kNormalBlock == c->GetId()) {
		for (auto& hitDirection : hitDirection_)
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
		auto& transform = gameObjectManager_->GetObj3dData(INameable::name_)->GetWorldTransform().transform;
		transform.translate.x += extrusion_.x;
		transform.translate.y += extrusion_.y;
	}
}
