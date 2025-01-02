#include "IObjectData.h"

IObjectData::IObjectData()
{
	gameObjectManager_ = GameObjectManager::GetInstance();
	collider_ = make_unique<ICollider>();
}

void IObjectData::CalcGravity(float g)
{
	velocity_.y += g;

}

void IObjectData::SetColliderParamData()
{

	objectData_ = gameObjectManager_->GetObj3dData(INameable::name_);
	auto data = objectData_.lock();
	collider_->SetObjectData(gameObjectManager_->GetObj3dData(INameable::name_)->GetWorldTransform().transform);
	collider_->SetAABB(data->GetAABB());
	collider_->SetOnCollisionFunc(std::bind(&IObjectData::OnCollision, this, std::placeholders::_1));
}

void IObjectData::SetObjectParamData()
{
	objectData_ = gameObjectManager_->GetObj3dData(INameable::name_);
}




