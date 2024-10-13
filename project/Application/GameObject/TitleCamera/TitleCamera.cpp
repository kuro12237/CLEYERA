#include "TitleCamera.h"

void TitleCamera::Initialize()
{
	name_ = "TitleCamera";

	CreateJsonData();

	///�J�����̃Z�b�g
	gameObjectManager_->CameraReset(name_);


	globalVariables_->AddItem(name_, "speed", speed_);
	speed_ = globalVariables_->GetValue<float>(name_, "speed");
	globalVariables_->AddItem(name_, "archOffsetAdd", archOffsetAdd_);
	archOffsetAdd_ = globalVariables_->GetValue<float>(name_, "archOffsetAdd");
}

void TitleCamera::Update()
{
	speed_ = globalVariables_->GetValue<float>(name_, "speed");
	archOffsetAdd_ = globalVariables_->GetValue<float>(name_, "archOffsetAdd");

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
