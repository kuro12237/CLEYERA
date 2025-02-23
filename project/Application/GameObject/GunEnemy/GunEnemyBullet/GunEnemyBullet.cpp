#include "GunEnemyBullet.h"

void GunEnemyBullet::Initialize()
{
	//auto& transform = gameObjectManager_->GetObj3dData(INameable::name_)->GetWorldTransform().transform;

	const AABB aabb = { {-0.1f,-0.1f,-0.1f,},{0.1f,0.1f,0.1f} };
	
	//dataをセット
	objectData_ = gameObjectManager_->GetObj3dData(INameable::name_);

	//コライダーセット
	this->SetColliderParamData();
	collider_->SetAABB(aabb);
	collider_->SetId(ObjectId::kGunEnemyBulletId);
	collider_->SetMask(CollisionMask::kEnemyWalkMask);
	collider_->SetAttribute(CollisionMask::kEnemyWalkAttribute);

}

void GunEnemyBullet::Update()
{
	//回転適用
	float velocityXZ = sqrt(pow(velocity_.x, 2.0f) + pow(velocity_.z, 2.0f));
	float height = -velocity_.y;
	Math::Vector::Vector3 rotate = {};
	rotate.y = std::atan2(velocity_.x, velocity_.z);
	rotate.x = std::atan2(height, velocityXZ);
	
	auto& transform = gameObjectManager_->GetObj3dData(this->INameable::name_)->GetWorldTransform();
	
	transform.transform.rotate = rotate;
	transform.transform.translate.x += velocity_.x;

	deltaTime_ += DeltaTimer(flame_);
	if (deltaTime_ >= deltaTimeMax_)
	{
		isDead_ = true;
	}

}

void GunEnemyBullet::OnCollision(ObjectComponent* objData)
{
	auto c = objData->GetCollider();
	c, objData;
	if (c->GetId() == ObjectId::kEnemyWalkId)
	{
		return;
	}

	if (c->GetId() == ObjectId::kGunEnemyId)
	{
		return;
	}

	if (c->GetId() == ObjectId::kPlayerId)
	{
		isDead_ = true;
	}
	if (c->GetId() == ObjectId::kNormalBlock)
	{
		isDead_ = true;
	}

}
