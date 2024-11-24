#include "GunEnemyBullet.h"

void GunEnemyBullet::Initialize()
{
}

void GunEnemyBullet::Update()
{
	auto &transform= gameObjectManager_->GetObj3dData(this->INameable::name_)->GetWorldTransform();

	transform.transform.translate.x += velocity_.x;

}

void GunEnemyBullet::OnCollision(ICollider* c, IObjectData* objData)
{
	c, objData;
	isDead_ = true;
}
