#include "ClearCamera.h"

void ClearCamera::Initilaize()
{
	name_ = "Camera";

	string paramFileName = gameObjectManager_->GetCameraData(name_)->GetParamFilePaths()[0];

	railData_ = RailLoader::LoadRail(paramFileName);

	splineMotion_ = make_unique<SplineMotion>();
	splineMotion_->SetP_RailData(railData_);
	splineMotion_->SetIsStartFlag(true);
}

void ClearCamera::Update()
{
	auto& wt = gameObjectManager_->GetCameraData(name_)->GetWorldTransform();

	if (splineMotion_)
	{
		if (splineMotion_->GetIsStartFlag())
		{
			wt.transform.translate = splineMotion_->CatmullRomInterpolation();
			splineMotion_->UpdateParamerter(60.0f);
		}
		if (splineMotion_->GetIsComplete())
		{
			splineMotion_.release();
			isComplete_ = true;
		}
	}
}
