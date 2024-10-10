#include "Tower.h"

void Tower::Initialize(string name, uint32_t index)
{
	name_ = name;
	index_ = index;
	gameObjectManager_ = GameObjectManager::GetInstance();

}

void Tower::Update()
{
	if (isSetNewPos_)
	{
		auto& data= gameObjectManager_->GetObjInstancingData(name_)->GetTransforms()[index_];
		data->GetTransform().translate = newPos_;
		isSetNewPos_ = false;
	}

}

void Tower::SetPos(const Math::Vector::Vector3& newPos)
{
	isSetNewPos_ = true;
	newPos_ = newPos;
}
