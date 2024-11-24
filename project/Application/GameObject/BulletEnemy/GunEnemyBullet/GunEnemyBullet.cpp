#include "GunEnemyBullet.h"

void GunEnemyBullet::Initialize()
{
	auto& transform = gameObjectManager_->GetObj3dData(INameable::name_)->GetWorldTransform().transform;
	SetObjectData(transform);

	Math::Vector::Vector2 minmax = { -0.5f,0.5f };
	aabb_ = { Math::Vector::Multiply(transform.scale,minmax.x), Math::Vector::Multiply(transform.scale,minmax.y) };

	id_ = kEnemyWalkId;
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

}

void GunEnemyBullet::OnCollision(ICollider* c, IObjectData* objData)
{
	c, objData;
	if (c->GetId() == kPlayerId)
	{
		isDead_ = true;
		return;
	}


}
