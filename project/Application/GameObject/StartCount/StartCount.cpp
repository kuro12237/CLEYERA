#include "StartCount.h"

void StartCount::Initialize()
{
	//tex
	numberTex_ = TextureManager::LoadPngTexture("GameObject/number/number.png");
	Math::Vector::Vector2 numberTexSize = TextureManager::GetTextureSize(numberTex_);
	//512�ɕ␳
	numberTexSize.x *= 0.25f;
	numberTexSize.x *= 0.5f;
	numberTexSize.y *= 0.5f;

	//init
	numberSprite_ = make_unique<Sprite>();
	numberSprite_->Initialize(new SpriteBoxState, { numberTexSize.x * -0.5f,numberTexSize.y * -0.5f });
	numberSprite_->SetTexHandle(numberTex_);
	numberSprite_->SetSize(numberTexSize);
	numberSprite_->SetSrc({ 0.0f,0.0f }, { 0.0f,1.0f }, { 0.25f,0.0f }, { 0.25f,1.0f });

	Math::Vector::Vector2 center = { float(WinApp::GetkCilientWidth() / 2),float(WinApp::GetkCilientHeight() / 2) };
	numberWorldTransform_.Initialize();
	numberWorldTransform_.transform.translate = { center.x,center.y,0.0f };
}

void StartCount::Update()
{
	if (countUpdateFlag_)
	{
		return;
	}
	float rotateMax = float(numbers::pi) * 2.0f;
	float flameMax = 1.0f;

	numberAnimationFlame_ += 1.0f / 180.0f;
	numberWorldTransform_.transform.rotate.z = Math::Vector::easeOutExpo(0.0f, rotateMax, numberAnimationFlame_);

	if (numberAnimationFlame_ >= flameMax)
	{
		numberAnimationFlame_ = 0.0f;
		count++;
		numberSprite_->GetuvTranslate().x += 0.25f;
		if (count >= 3)
		{
			startFlag = true;
			countUpdateFlag_ = true;
			countDrawFlag_ = true;
		}
	}

	numberWorldTransform_.UpdateMatrix();
}

void StartCount::Draw2d()
{
	if (countDrawFlag_)
	{
		return;
	}
	numberSprite_->Draw(numberWorldTransform_);
}
