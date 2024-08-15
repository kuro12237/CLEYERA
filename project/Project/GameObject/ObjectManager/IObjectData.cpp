#include "IObjectData.h"

void IObjectData::GetData(GameObjectManager* data)
{
	worldMat_ = &data->GetObj3dData(name_)->GetWorldTransform().matWorld;
}

void IObjectData::CalcGravity(float g)
{
	velocity_.y += g;
	auto& transform = GameObjectManager::GetInstance()->GetObj3dData(name_)->GetWorldTransform().transform;
	transform.translate.y += velocity_.y;
}

