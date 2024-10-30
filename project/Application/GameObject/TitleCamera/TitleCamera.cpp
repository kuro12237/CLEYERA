#include "TitleCamera.h"

void TitleCamera::Initialize()
{
	name_ = "TitleCamera";

	CreateJsonData();

	///カメラのセット
	gameObjectManager_->CameraReset(name_);
	this->jsonGropName_ = name_;
	this->AddJsonItem("speed", speed_);
	speed_ = this->GetJsonItem<float>("speed");
	this->AddJsonItem("archOffsetAdd", archOffsetAdd_);
	archOffsetAdd_ = this->GetJsonItem<float>("archOffsetAdd");
}

void TitleCamera::Update()
{
	archOffsetAdd_ = this->GetJsonItem<float>("archOffsetAdd");
	speed_ = this->GetJsonItem<float>("speed");

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
		archStartOffset_ += archOffsetAdd_;
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
