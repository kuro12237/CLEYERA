#include "StartCameraMotion.h"

void StartCameraMotion::Initilaize(const uint32_t& index)
{
	name_ = "StartCamera";

	cameraIndex_ = index;

	string paramFileName = gameObjectManager_->GetCameraData(name_)->GetParamFilePaths()[0];

	railData_ = RailLoader::LoadRail(paramFileName);

	splineMotion_ = make_unique<SplineMotion>();
	splineMotion_->SetP_RailData(railData_);
}

void StartCameraMotion::Update()
{
	auto& wt = gameObjectManager_->GetCameraData(name_)->GetWorldTransform();

	if (isStartFlag_)
	{
		wt.transform.translate = splineMotion_->CatmullRomInterpolation();
		splineMotion_->UpdateParamerter(480.0f);
	}
	if (splineMotion_->GetIsComplete())
	{

	}
}

void StartCameraMotion::DrawLines()
{
}
