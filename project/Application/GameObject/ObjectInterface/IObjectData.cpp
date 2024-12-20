#include "IObjectData.h"

IObjectData::IObjectData()
{
	gameObjectManager_ = GameObjectManager::GetInstance();
}

void IObjectData::CalcGravity(float g)
{
	velocity_.y += g;
	auto& transform = GameObjectManager::GetInstance()->GetObj3dData(name_)->GetWorldTransform().transform;
	transform.translate.y += velocity_.y;
}




