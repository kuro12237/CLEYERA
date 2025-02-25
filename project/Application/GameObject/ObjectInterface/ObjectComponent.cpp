#include "ObjectComponent.h"

ObjectComponent::ObjectComponent()
{
	gameObjectManager_ = GameObjectManager::GetInstance();
	collider_ = make_unique<Collider>();
}

void ObjectComponent::CalcGravity(float g)
{
	velocity_.y += g;
}

void ObjectComponent::SetColliderParamData()
{

	objectData_ = gameObjectManager_->GetObj3dData(INameable::name_);
	auto data = objectData_.lock();
	collider_->SetObjectData(gameObjectManager_->GetObj3dData(INameable::name_)->GetWorldTransform().transform);
	collider_->SetAABB(data->GetAABB());
	collider_->SetOnCollisionFunc(std::bind(&ObjectComponent::OnCollision, this, std::placeholders::_1));
}

void ObjectComponent::SetObjectParamData()
{
	objectData_ = gameObjectManager_->GetObj3dData(INameable::name_);
}




