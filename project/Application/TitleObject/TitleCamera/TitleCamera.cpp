#include "TitleCamera.h"

void TitleCamera::Initialize()
{
	gameObjectManager_ = GameObjectManager::GetInstance();

	this->name_ = "TitleCamera";
	gameObjectManager_->CameraReset(name_);

}

void TitleCamera::Update()
{
	//auto& cameraWt = gameObjectManager_->GetCameraData(name_)->GetWorldTransform();

	//cameraWt.transform.translate.z += speed_;

}
