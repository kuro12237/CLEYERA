#include "TitleCamera.h"

void TitleCamera::Initialize()
{
	gameObjectManager_ = GameObjectManager::GetInstance();

	this->name_ = "TitleCamera";
	gameObjectManager_->CameraReset(name_);

}

void TitleCamera::Update()
{
	if (isBridgeAnimationStart_)
	{
		isBridgeAnimationStart_ = false;
	}

	auto& cameraWt = gameObjectManager_->GetCameraData(name_)->GetWorldTransform();

	if (isCameraMove_)
	{
		cameraWt.transform.translate.z += speed_;
	}

	if (cameraWt.transform.translate.z > archStartOffset_)
	{
		string number = to_string((archStartOffset_));
		LogManager::Log(number + "\n");
		archStartOffset_ += 32.0f;
		isBridgeAnimationStart_ = true;
		if (useBridgeNumber_ == 0)
		{
			useBridgeNumber_ = 1;
			return;
		}
		if (useBridgeNumber_ == 1)
		{
			useBridgeNumber_ = 0;
			return;
		}
	}

}
