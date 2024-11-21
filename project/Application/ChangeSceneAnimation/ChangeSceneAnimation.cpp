#include "ChangeSceneAnimation.h"


using namespace Engine;
using namespace Engine::Objects;
using namespace Engine::Manager;
using namespace Engine::Transform;

ChangeSceneAnimation* ChangeSceneAnimation::GetInstance()
{
	static ChangeSceneAnimation instance;
	return &instance;
}

void ChangeSceneAnimation::Initialize()
{
	if (initializeLock_)
	{
		return;
	}
	initializeLock_ = true;

	///ノイズのテクスチャを読み込む
	uint32_t noiseTexHandle= TextureManager::LoadPngTexture("GameObject/Noise/Noise.png");

	titleName2d_ = make_unique<TitleName2d>();
	titleName2d_->Initialize(noiseTexHandle);
	titleName2d_->SetP_DissolveMask(dissolveMask_);

	titleBack2d_ = make_unique<TitleBack2d>();
	titleBack2d_->Initialize(noiseTexHandle);
	titleBack2d_->SetP_DissolveMask(dissolveMask_);

	rodingIcon_ = make_unique<RodingIcon2d>();
	rodingIcon_->Initialize(noiseTexHandle);
	rodingIcon_->SetP_DissolveMask(dissolveMask_);
}

void ChangeSceneAnimation::ImGuiUpdate()
{
	titleBack2d_->ImGuiUpdate();
	titleName2d_->ImGuiUpdate();
	rodingIcon_->ImGuiUpdate();
}

void ChangeSceneAnimation::Update()
{

	isChangeSceneFlag_ = false;
	//スタート時
	if (isUpdateFlag_)
	{
		flame_ += 1.0f / 120.0f;
	}
	//前半
	if (isStartFlag_)
	{
		//補間
		dissolveMask_ = Math::Vector::EaseOutQuad(dissolveMax_, 0.0f, flame_);

		if (dissolveMask_ <= 0.0f)
		{
			flame_ = 0.0f;
			isStartFlag_ = false;
			isEndFlag_ = true;
			isChangeSceneFlag_ = true;
		}
	}
	//後半
	if (isEndFlag_)
	{
		dissolveMask_ = Math::Vector::EaseOutQuad(0.0f, dissolveMax_, flame_);
		if (dissolveMask_ >= dissolveMax_)
		{
			flame_ = 0.0f;
			isEndFlag_ = false;
			isUpdateFlag_ = false;
			isCompliteFlag_ = true;
		}
	}

	titleName2d_->Update();
	titleBack2d_->Update();
	rodingIcon_->Update();
}

void ChangeSceneAnimation::Draw()
{

	if (isCompliteFlag_)
	{
		return;
	}

	titleBack2d_->Draw2d();
	titleName2d_->Draw2d();
	rodingIcon_->Draw2d();
}

void ChangeSceneAnimation::ChangeStart()
{
	if (isCompliteFlag_)
	{
		isStartFlag_ = true;
		isUpdateFlag_ = true;
		isEndFlag_ = false;
		isCompliteFlag_ = false;
	}
}
