#include "StartAnimation.h"

using namespace Engine::Transform;

void StartAnimation::Initialize()
{
	gameObjectManager_ = GameObjectManager::GetInstance();

	startCount_ = make_unique<StartCount>();
	startCount_->Initialize();

	railData_.resize(splineMotionsMax_);
	splineMotions_.resize(splineMotionsMax_);



	for (uint32_t i = 0; i < splineMotionsMax_; i++)
	{
		string paramFiles = gameObjectManager_->GetCameraData(selectCameraName_ + FormatNumberWithDots(int(i)))->GetParamFilePaths()[0];

		RailData railData = RailLoader::LoadRail(paramFiles);
		railData_[i] = railData;

		splineMotions_[i] = make_unique<SplineMotion>();
		splineMotions_[i]->SetP_RailData(railData_[i]);
	}
	gameObjectManager_->CameraReset(selectCameraName_);
	splineMotions_[0]->SetIsStartFlag(true);

	gameObjectManager_->CameraReset("PlayerCamera");
}

void StartAnimation::Update()
{
	if (!isCountStart_)
	{
		return;
	}

	/*
	auto& camera = gameObjectManager_->GetCameraData(selectCameraName_)->GetWorldTransform();

	for (size_t i = 0; i < size_t(splineMotionsMax_); i++)
	{
		if (!splineMotions_[i])
		{
			continue;
		}

		if (splineMotions_[i]->GetIsStartFlag())
		{
			splineMotions_[i]->UpdateParamerter(480.0f);
			camera.transform.translate = splineMotions_[i]->CatmullRomInterpolation();
		}

		if (splineMotions_[i]->GetIsComplete())
		{
			splineMotions_[i].release();

			if (i == 1)
			{
				isStartCount_ = true;
				startCount_->SetStartFlag(true);
				gameObjectManager_->CameraReset("PlayerCamera");

				break;
			}
			else
			{
				selectCameraName_ = selectCameraName_ + FormatNumberWithDots(int(i + 1));
				splineMotions_[i + 1]->SetIsStartFlag(true);
				gameObjectManager_->CameraReset(selectCameraName_);
			}
		}
	}*/
	

	isStartCount_ = true;
	if (!isStartCount_)
	{
		return;
	}

	startCount_->Update();

	///カウントダウン完了したら
	if (startCount_->GetStartFlag())
	{
		isGameStart_ = true;
	}
}

void StartAnimation::DebugLine()
{
}

void StartAnimation::Draw2d()
{
	startCount_->Draw2d();
}
