#include "IGameSceneAnimation.h"

void IGameSceneAnimation::SettingSplineMotionData()
{
	splineMotions_.resize(splineMotionsMax_);
	for (uint32_t i = 0; i < splineMotionsMax_; i++)
	{
		splineMotions_[i] = make_unique<SplineMotion>();
		splineMotions_[i]->SetP_RailData(railData_[i]);
	}
}

void IGameSceneAnimation::LoadRailData()
{
	railData_.resize(splineMotionsMax_);

	for (uint32_t i = 0; i < splineMotionsMax_; i++)
	{
		string paramFile = gameObjectManager_->GetCameraData(cameraName_ + FormatNumberWithDots(int(i)))->GetParamFilePaths()[0];
		railData_[i] = RailLoader::LoadRail(paramFile);
	}
}

Math::Vector::Vector3 IGameSceneAnimation::CalcRailData(const size_t& index, const float& flame)
{
	splineMotions_[index]->UpdateParamerter(flame);
	Math::Vector::Vector3 result = splineMotions_[index]->CatmullRomInterpolation();
	return result;
}
