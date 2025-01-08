#include "StartAnimation.h"

using namespace Engine::Transform;

using namespace Engine;
using namespace Engine::Objects;
using namespace Engine::Manager;

void StartAnimation::Initialize(uint32_t stageNum)
{
	stageNum;
	gameObjectManager_ = GameObjectManager::GetInstance();
	postEffect_ = PostEffect::GetInstance();

	startCount_ = make_unique<StartCount>();
	startCount_->Initialize();
	this->cameraName_ = "StartCamera";
	this->splineMotionsMax_ = 1;
	railData_.resize(splineMotionsMax_);
	splineMotions_.resize(splineMotionsMax_);


	splineSelectIndex_ = 0;

	this->LoadRailData();
	this->SettingSplineMotionData();

	gameObjectManager_->CameraReset(cameraName_);
	splineMotions_[0]->SetIsStartFlag(true);
	isCountStart_ = true;

	const float vinatteScaleMax = 10.0f;

	postEffect_->SetVignetteScale(vinatteScaleMax);
	postEffect_->SetSelectPostEffect(VIGNETTE, true);
	postEffect_->SetVignetteColor({});

	state_ = make_unique<StartAnimationStateCamera>();
	state_->Initialize();

}

void StartAnimation::Update()
{
	if (!isCountStart_)
	{
		return;
	}

	if (state_)
	{
		state_->Update(*this);
	}

	FlameUpdate();

	auto& camera = gameObjectManager_->GetCameraData(cameraName_)->GetWorldTransform();

	for (size_t i = 0; i < size_t(splineMotionsMax_); i++)
	{
		if (!splineMotions_[i])
		{
			continue;
		}

		if (splineMotions_[i]->GetIsComplete())
		{
			splineSelectIndex_++;
			splineMotions_[i].release();

			if (i == splineMotionsMax_ - 1)
			{
				isStartCount_ = true;
				gameObjectManager_->CameraReset("PlayerCamera");
				break;
			}

			continue;
		}

		if (splineMotions_[i]->GetIsStartFlag())
		{
			//レールを計算
			camera.transform.translate = CalcRailData(i, 180.0f);

			if (Input::PushBottonPressed(XINPUT_GAMEPAD_A))
			{
				isSkip_ = true;
			}

			SkipAnimation();

			if (!isSkip_)
			{
				//ビネットの呼び出し
				EndUpdate([this]() {EndVinatteAnimation(); });
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
		const float addFlame = 1.0f / 120.0f;
		flameCount_ += addFlame;
	}
}

void StartAnimation::EndVinatteAnimation()
{
	//終わり
	if (splineMotions_[splineSelectIndex_]->GetTargetIndex() == railData_[splineSelectIndex_].size - 2)
	{
		postEffect_->SetSelectPostEffect(VIGNETTE, true);
		isFlameCount_ = true;
		vinatteFlame_ = Math::Vector::LerpEaseOutSine(0.0f, 20.0f, flameCount_);

		if (vinatteFlame_ >= 10.0f)
		{
			splineMotions_[splineSelectIndex_]->SetIsComplete(true);
			flameCount_ = 0.0f;
			isFlameCount_ = false;
		}
	}
}

void StartAnimation::SkipAnimation()
{
	if (!isSkip_)
	{
		return;
	}
	postEffect_->SetSelectPostEffect(VIGNETTE, true);
	isFlameCount_ = true;
	vinatteFlame_ = Math::Vector::LerpEaseOutSine(0.0f, 20.0f, flameCount_);

	if (vinatteFlame_ >= 10.0f)
	{

		splineMotions_[splineSelectIndex_]->SetIsComplete(true);
		flameCount_ = 0.0f;
		isFlameCount_ = false;
	}
}
