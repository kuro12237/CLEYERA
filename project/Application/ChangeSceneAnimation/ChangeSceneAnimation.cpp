#include "ChangeSceneAnimation.h"

ChangeSceneAnimation* ChangeSceneAnimation::GetInstance()
{
	static ChangeSceneAnimation instance;
	return &instance;
}

void ChangeSceneAnimation::Initialize()
{
	center_ = { float(WinApp::GetkCilientWidth() / 2), float(WinApp::GetkCilientHeight() / 2) };
	Math::Vector::Vector4 edgeColor = ColorConverter::ColorConversion(edgeColor_16);

	sprite_ = make_unique<Sprite>();
	sprite_->Initialize();
	tex_ = TextureManager::LoadPngTexture("GameObject/ChangeScene/ChangeScene.png");
	noiseTex_.resize(1);
	noiseTex_[0] = TextureManager::LoadPngTexture("GameObject/Noise/Noise.png");

	sprite_->SetTexHandle(tex_);
	sprite_->SetNoiseTex(noiseTex_[0]);
	sprite_->SetSpriteMode(DissolveNone);
	//dissolve設定
	sprite_->GetDissolveMask() = dissolveMax;
	sprite_->GetDissolveEdgeMinMax() = { 0.0f, 0.06f };
	sprite_->GetDissolveDdgeColor() = edgeColor;

	titleNameSprite_ = make_unique<Sprite>();
	titleNameSprite_->Initialize();
	uint32_t handle = TextureManager::LoadPngTexture("TitleName.png");
	titleNameSprite_->SetTexHandle(handle);
	titleNameSprite_->SetNoiseTex(noiseTex_[0]);
	titleNameSprite_->SetSpriteMode(DissolveNone);
	//dissolve設定
	titleNameSprite_->GetDissolveMask() = dissolveMax;
	titleNameSprite_->GetDissolveEdgeMinMax() = { 0.0f, 0.06f };
	titleNameSprite_->GetDissolveDdgeColor() = edgeColor;

	wT_.Initialize();
	titleNameWt_.Initialize();
}

void ChangeSceneAnimation::Update()
{
	if (isCompliteFlag_)
	{
		return;
	}

	isChangeSceneFlag_ = false;
	//スタート時
	if (isUpdateFlag_)
	{
		flame_ += 1.0f / 120.0f;
	}
	//前半
	if (isStartFlag_)
	{
		dissolveMask_ = Math::Vector::EaseOutQuad(dissolveMax, 0.0f, flame_);

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
		dissolveMask_ = Math::Vector::EaseOutQuad(0.0f, dissolveMax, flame_);
		if (dissolveMask_ >= dissolveMax)
		{
			flame_ = 0.0f;
			isEndFlag_ = false;
			isUpdateFlag_ = false;
			isCompliteFlag_ = true;
		}
	}


	sprite_->GetDissolveMask() = dissolveMask_;
	titleNameSprite_->GetDissolveMask() = dissolveMask_;

	titleNameWt_.UpdateMatrix();
	wT_.UpdateMatrix();
}

void ChangeSceneAnimation::Draw()
{
	if (isCompliteFlag_)
	{
		return;
	}
	sprite_->Draw(wT_);
	titleNameSprite_->Draw(titleNameWt_);
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
