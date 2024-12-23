#include "GunEnemyPart.h"

void GunEnemyPart::Initialize()
{
	auto& transform = gameObjectManager_->GetObj3dData(INameable::name_)->GetWorldTransform().transform;

	const Math::Vector::Vector2 minmax = { -1.0f,1.0f };
	AABB aabb = { Math::Vector::Multiply(transform.scale,minmax.x), Math::Vector::Multiply(transform.scale,minmax.y) };

	//dataをセット
	objectData_ = gameObjectManager_->GetObj3dData(INameable::name_);

	//コライダーセット
	this->SetColliderParamData();
	collider_->SetAABB(aabb);
	collider_->SetId(ObjectId::kGunEnemyId);
	collider_->SetIsExtrusion(true);
	collider_->SetMask(CollisionMask::kEnemyWalkMask);
	collider_->SetAttribute(CollisionMask::kEnemyWalkAttribute);

}

void GunEnemyPart::Update()
{
	if (*isCoreEnd_ && !isEnd_)
	{
		collider_->SetId(ObjectId::kOnlyCollideWithBlocksid);
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

void GunEnemyPart::OnCollision([[maybe_unused]] IObjectData* objData)
{
	IsHit_ = true;
	auto c = objData->GetCollider();

	//ブロックとの処理
	if (ObjectId::kNormalBlock == c->GetId()) {
		for (auto& hitDirection : c->GetHItDirection())
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
		
		transform.translate.x += c->GetExtrusion().x;
		transform.translate.y += c->GetExtrusion().y;
	}
}
