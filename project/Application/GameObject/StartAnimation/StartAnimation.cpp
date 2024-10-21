#include "StartAnimation.h"

using namespace Engine::Transform;

void StartAnimation::Initialize()
{
	gameObjectManager_ = GameObjectManager::GetInstance();
	postEffect_ = PostEffect::GetInstance();

	startCount_ = make_unique<StartCount>();
	startCount_->Initialize();

	railData_.resize(splineMotionsMax_);
	splineMotions_.resize(splineMotionsMax_);

	for (uint32_t i = 0; i < splineMotionsMax_; i++)
	{
		string paramFile = gameObjectManager_->GetCameraData(selectCameraName_ + FormatNumberWithDots(int(i)))->GetParamFilePaths()[0];
		railData_[i] = RailLoader::LoadRail(paramFile);

		splineMotions_[i] = make_unique<SplineMotion>();
		splineMotions_[i]->SetP_RailData(railData_[i]);
	}
	gameObjectManager_->CameraReset(selectCameraName_);
	splineMotions_[0]->SetIsStartFlag(true);
	isCountStart_ = true;


	postEffect_->SetVignetteFactor(1.0f);
	postEffect_->SetVignetteColor({ 0.0f,0.0f,0.0f });
}

void StartAnimation::Update()
{
	if (!isCountStart_)
	{
		return;
	}

	auto& camera = gameObjectManager_->GetCameraData(selectCameraName_)->GetWorldTransform();

	for (size_t i = 0; i < size_t(splineMotionsMax_); i++)
	{
		if (!splineMotions_[i])
		{
			continue;
		}

		if (splineMotions_[i]->GetIsComplete())
		{
			splineMotions_[i].release();

			if (i == splineMotionsMax_ - 1)
			{
				isStartCount_ = true;
				gameObjectManager_->CameraReset("PlayerCamera");
				break;
			}
			else
			{
				selectCameraName_ = selectCameraName_ + FormatNumberWithDots(int(i + 1));
				splineMotions_[i + 1]->SetIsStartFlag(true);
				gameObjectManager_->CameraReset(selectCameraName_);
			}
			continue;
		}

		if (splineMotions_[i]->GetIsStartFlag())
		{
			splineMotions_[i]->UpdateParamerter(180.0f);
			camera.transform.translate = splineMotions_[i]->CatmullRomInterpolation();

			//終わり
			if (splineMotions_[i]->GetTargetIndex() == railData_[i].size - 2)
			{
				vinatteFlame_ = Math::Vector::LerpEaseOutSine(vinatteScaleMax_, 0.0f, splineMotions_[i]->GetFlame());
				postEffect_->SetSelectPostEffect(VIGNETTE, true);
				postEffect_->SetVignetteScale(vinatteFlame_);
				if (vinatteFlame_ > vinatteScaleMax_ - 1.0f)
				{

					postEffect_->SetVignetteScale(vinatteScaleMax_);
				}
			}
			//始まり
			if (splineMotions_[i]->GetTargetIndex() == 0)
			{
				if (postEffect_->GetIsUseVinatte())
				{
					vinatteFlame_ = Math::Vector::LerpEaseInSine(0.0f, vinatteScaleMax_, splineMotions_[i]->GetFlame());
					postEffect_->SetVignetteScale(vinatteFlame_);
					if (vinatteFlame_ > vinatteScaleMax_ - 1.0f)
					{
						postEffect_->SetSelectPostEffect(VIGNETTE, false);
					}
				}
			}

		}
	}


	if (!isStartCount_)
	{
		return;
	}


	if (postEffect_->GetIsUseVinatte())
	{
		flameCount_ += 1.0f / 180.0f;
		vinatteFlame_ = Math::Vector::LerpEaseInSine(0.0f, vinatteScaleMax_, flameCount_);
		postEffect_->SetVignetteScale(vinatteFlame_);
		if (vinatteFlame_ >= vinatteScaleMax_ - 1.0f)
		{
			postEffect_->SetSelectPostEffect(VIGNETTE, false);
		}
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
	if (!isStartCount_)
	{
		return;
	}
	startCount_->Draw2d();

}
