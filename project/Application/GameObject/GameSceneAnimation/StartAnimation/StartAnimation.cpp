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

	this->cameraName_ = "StartCamera";
	this->splineMotionsMax_ = 1;
	splineSelectIndex_ = 0;

	this->LoadRailData();
	this->SettingSplineMotionData();



	gameObjectManager_->CameraReset(cameraName_);
	splineMotions_[0]->SetIsStartFlag(true);
	isCountStart_ = true;


	postEffect_->SetVignetteScale(10.0f);
	postEffect_->SetSelectPostEffect(VIGNETTE, true);
	postEffect_->SetVignetteColor({ 0.0f,0.0f,0.0f });

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
			else
			{
				cameraName_ = cameraName_ + FormatNumberWithDots(int(i + 1));
				splineMotions_[i + 1]->SetIsStartFlag(true);
				gameObjectManager_->CameraReset(cameraName_);
			}

			continue;
		}

		if (splineMotions_[i]->GetIsStartFlag())
		{
			//���[�����v�Z
			camera.transform.translate = CalcRailData(i, 180.0f);
			//�r�l�b�g�̌Ăяo��
			EndUpdate([this]() {EndVinatteAnimation(); });
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

	///�J�E���g�_�E������������
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

void StartAnimation::EndVinatteAnimation()
{
	//�I���
	if (splineMotions_[splineSelectIndex_]->GetTargetIndex() == railData_[splineSelectIndex_].size - 2)
	{
		postEffect_->SetSelectPostEffect(VIGNETTE, true);
		isFlameCount_ = true;
		vinatteFlame_ = Math::Vector::LerpEaseOutSine(0.0f, 10.0f, splineMotions_[splineSelectIndex_]->GetFlame());

		if (vinatteFlame_ >= 10.0f)
		{
			isFlameCount_ = false;
		}
	}
}