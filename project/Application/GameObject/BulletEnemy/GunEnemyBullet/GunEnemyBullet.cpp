#include "GunEnemyBullet.h"

void GunEnemyBullet::Initialize()
{
	auto& transform = gameObjectManager_->GetObj3dData(INameable::name_)->GetWorldTransform().transform;
	SetObjectData(transform);


	const AABB aabb = { {-0.1f,-0.1f,-0.1f,},{0.1f,0.1f,0.1f} };
	aabb_ = aabb;
	id_ = kGunEnemyBulletId;
	attribute_ = CollisionMask::kEnemyWalkAttribute;
	mask_ = CollisionMask::kEnemyWalkMask;

	//回転適用
	float velocityXZ = sqrt(pow(velocity_.x, 2.0f) + pow(velocity_.z, 2.0f));
	float height = -velocity_.y;
	Math::Vector::Vector3 rotate = {};
	rotate.y = std::atan2(velocity_.x, velocity_.z);
	rotate.x = std::atan2(height, velocityXZ);
	transform.rotate = rotate;
}

void GunEnemyBullet::Update()
{
	auto &transform= gameObjectManager_->GetObj3dData(this->INameable::name_)->GetWorldTransform();

	transform.transform.translate.x += velocity_.x;

	deltaTime_ += DeltaTimer(flame_);
	if (deltaTime_>=deltaTimeMax_)
	{
		isDead_ = true;
	}

}

void GunEnemyBullet::OnCollision(ICollider* c, IObjectData* objData)
{
	c, objData;
	if (c->GetId()==kEnemyWalkId)
	{
		return;
	}

	if (c->GetId()==kGunEnemyId)
	{
		return;
	}

	if (c->GetId() == kPlayerId)
	{
		isDead_ = true;
	}
	if (c->GetId() == kNormalBlock)
	{
		isDead_ = true;
	}

}
