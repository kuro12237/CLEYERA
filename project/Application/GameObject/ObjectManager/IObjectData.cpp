#include "IObjectData.h"

void IObjectData::CalcGravity(float g)
{
	velocity_.y += g;
	auto& transform = GameObjectManager::GetInstance()->GetObj3dData(name_)->GetWorldTransform().transform;
	transform.translate.y += velocity_.y;
}

void IObjectData::CreateJsonData()
{
	globalVariables_ = GlobalVariables::GetInstance();
	globalVariables_->CreateGroup(name_);
}

