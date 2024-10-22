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


	postEffect_->SetVignetteScale(10.0f);
	postEffect_->SetSelectPostEffect(VIGNETTE, true);
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
				postEffect_->SetSelectPostEffect(VIGNETTE, true);
				isFlameCount_ = true;
				vinatteFlame_ = Math::Vector::LerpEaseOutSine(0.0f, 10.0f, splineMotions_[i]->GetFlame());

				if (vinatteFlame_ >=10.0f)
				{
					isFlameCount_ = false;
				}
			}
		}
	}
	postEffect_->SetVignetteFactor(vinatteFlame_);


	if (!isStartCount_)
	{
		return;
	}


	if (postEffect_->GetIsUseVinatte())
	{
		isFlameCount_ = true;
		vinatteFlame_ = Math::Vector::LerpEaseOutSine(10.0f,0.0f, flameCount_);
		if (flameCount_ >= 1.0f)
		{
			postEffect_->SetSelectPostEffect(VIGNETTE, false);
			isFlameCount_ = false;
			flameCount_ = 0.0f;
		}
	}

	FlameUpdate();

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

void StartAnimation::FlameUpdate()
{
	if ( isFlameCount_)
	{
		flameCount_ += 1.0f / 120.0f;
	}
}
