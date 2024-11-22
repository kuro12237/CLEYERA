#include "Lava.h"

void Lava::Initialize()
{
	name_ = "LavaPlane";
	gameObjectManager_ = GameObjectManager::GetInstance();
}

void Lava::Update()
{
	auto& wt = gameObjectManager_->GetObj3dData(name_)->GetWorldTransform();
	auto& objParam = gameObjectManager_->GetObj3dData(name_)->GetGameObject();
	auto& objDesc = gameObjectManager_->GetObj3dData(name_)->GetDesc();
	objDesc.colorDesc.uvTranslate.y += 10.0f;
	objParam->SetDesc(objDesc);
	
	if (p_CameraPos_)
	{
		wt.transform.translate.z = p_CameraPos_->z;
	}
}
