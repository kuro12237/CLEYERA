#include "ChangeSceneAnimation.h"

ChangeSceneAnimation* ChangeSceneAnimation::GetInstance()
{
	static ChangeSceneAnimation instance;
	return &instance;
}

void ChangeSceneAnimation::Initialize()
{
	center_ = { float(WinApp::GetkCilientWidth() / 2), float(WinApp::GetkCilientHeight() / 2) };

	sprite_ = make_unique<Sprite>();
	sprite_->Initialize();
	tex_ = TextureManager::LoadPngTexture("GameObject/ChangeScene/ChangeScene.png");
	noiseTex_.resize(1);
	noiseTex_[0] = TextureManager::LoadPngTexture("GameObject/Noise/Noise.png");

	sprite_->SetTexHandle(tex_);
	sprite_->SetNoiseTex(noiseTex_[0]);
	sprite_->SetSpriteMode(DissolveNone);
	//dissolve�ݒ�
	sprite_->GetDissolveMask() = dissolveMax;
	sprite_->GetDissolveEdgeMinMax() = { 0.0f, 0.06f };
	Math::Vector::Vector4 edgeColor = ColorConverter::ColorConversion(edgeColor_16);
	sprite_->GetDissolveDdgeColor() = edgeColor;

	wT_.Initialize();
}

void ChangeSceneAnimation::Update()
{
	if (isCompliteFlag_)
	{
		return;
	}

	isChangeSceneFlag_ = false;
	float& dissolveMask = sprite_->GetDissolveMask();
	//�X�^�[�g��
	if (isUpdateFlag_)
	{
		flame_ += 1.0f / 120.0f;
	}
	//�O��
	if (isStartFlag_)
	{
		dissolveMask = Math::Vector::EaseOutQuad(dissolveMax, 0.0f, flame_);

		if (dissolveMask <= 0.0f)
		{
			flame_ = 0.0f;
			isStartFlag_ = false;
			isEndFlag_ = true;
			isChangeSceneFlag_ = true;
		}
	}
	//�㔼
	if (isEndFlag_)
	{
		dissolveMask = Math::Vector::EaseOutQuad(0.0f, dissolveMax, flame_);
		if (dissolveMask >= dissolveMax)
		{
			flame_ = 0.0f;
			isEndFlag_ = false;
			isUpdateFlag_ = false;
			isCompliteFlag_ = true;
		}
	}

	wT_.UpdateMatrix();
}

void ChangeSceneAnimation::Draw()
{
	sprite_->Draw(wT_);
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
