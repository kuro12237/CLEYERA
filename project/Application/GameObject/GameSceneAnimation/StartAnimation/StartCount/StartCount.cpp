#include "StartCount.h"


using namespace Engine::Objects;
using namespace Engine::Transform;
using namespace Engine::Base::Win;

using namespace Engine;
using namespace Engine::Manager;
using namespace Engine::Transform;

void StartCount::Initialize()
{
	//tex
	numberTex_ = TextureManager::LoadDDSTexture("GameObject/number/number.dds");
	Math::Vector::Vector2 numberTexSize = TextureManager::GetTextureSize(numberTex_);
	//512に補正
	numberTexSize.x *= 0.25f;
	numberTexSize.x *= 0.5f;
	numberTexSize.y *= 0.5f;

	//init
	numberSprite_ = make_unique<Sprite>();
	numberSprite_->Initialize({ numberTexSize.x * -0.5f,numberTexSize.y * -0.5f });
	numberSprite_->SetTexHandle(numberTex_);
	numberSprite_->SetSize(numberTexSize);
	numberSprite_->SetSrc({ 0.0f,0.0f }, { 0.0f,1.0f }, { 0.25f,0.0f }, { 0.25f,1.0f });

	Math::Vector::Vector2 center = { float(WinApp::GetkCilientWidth() / 2),float(WinApp::GetkCilientHeight() / 2) };
	numberWorldTransform_.Initialize();
	numberWorldTransform_.transform.translate = { center.x,center.y,0.0f };

	//背景フレームの初期化
	backFlameTex_ = TextureManager::LoadDDSTexture("GameObject/BackFlame/BackFlame.dds");
	Math::Vector::Vector2 backFlameTexSize = TextureManager::GetTextureSize(backFlameTex_);
	backFlameSprite_ = make_unique<Sprite>();
	backFlameSprite_->Initialize({ backFlameTexSize.x * -0.5f,backFlameTexSize.y * -0.5f });
	backFlameSprite_->SetTexHandle(backFlameTex_);

	backFlameWt_.Initialize();
	float backFlameScale = 0.5f;
	backFlameWt_.transform.scale = { backFlameScale ,backFlameScale ,0.0f };
	backFlameWt_.transform.translate = { center.x,center.y,0.0f };

	//フレームの初期化
	size_t flameMax = 4;
	flameTex_ = TextureManager::LoadDDSTexture("GameObject/Flame/Flame.dds");
	Math::Vector::Vector2 flameTexSize = TextureManager::GetTextureSize(flameTex_);
	flameSprites_.resize(flameMax);
	flameWts_.resize(flameMax);

	//回転の設定
	vector<float>flameAngles;
	flameAngles.resize(flameMax);
	flameAngles[0] = float(numbers::pi) / 4.0f;
	flameAngles[1] = -float(numbers::pi) / 4.0f;
	flameAngles[2] = float(numbers::pi) / 4.0f + float(numbers::pi);
	flameAngles[3] = float(numbers::pi) / 2.0f + float(numbers::pi) / 4.0f;

	float posSize = 0.0f;
	//start地点
	startFlamePos_.resize(flameMax);
	startFlamePos_[0] = { center.x,center.y };
	startFlamePos_[1] = { center.x ,center.y };
	startFlamePos_[2] = { center.x,center.y };
	startFlamePos_[3] = { center.x ,center.y };

	//end地点
	posSize = 128.0f;
	endFlamePos_.resize(flameMax);
	endFlamePos_[0] = { center.x,center.y - posSize };
	endFlamePos_[1] = { center.x - posSize,center.y };
	endFlamePos_[2] = { center.x,center.y + posSize };
	endFlamePos_[3] = { center.x + posSize ,center.y };

	for (size_t i = 0; i < flameMax; i++)
	{
		unique_ptr<Sprite>sprite = make_unique<Sprite>();
		sprite->Initialize({ flameTexSize.x * -0.5f, flameTexSize.y * -0.5f });
		sprite->SetTexHandle(flameTex_);
		WorldTransform wt;
		wt.Initialize();
		float kScale = 0.125f;
		wt.transform.scale = { kScale,kScale,1.0f };
		wt.transform.rotate.z = flameAngles[i];
		wt.transform.translate = { startFlamePos_[i].x,startFlamePos_[i].y,0.0f };
		flameSprites_[i] = move(sprite);
		flameWts_[i] = move(wt);
	}

	//針の初期化
	const float radius = 128.0f;
	barTex_ = TextureManager::LoadDDSTexture("GameObject/Flame/bar.dds");
	Math::Vector::Vector2 barTexSize = TextureManager::GetTextureSize(barTex_);
	barSprites_.resize(BarMax);
	barWts_.resize(BarMax);

	for (size_t i = 0; i < BarMax; i++)
	{
		unique_ptr<Sprite>sprite = make_unique<Sprite>();
		sprite->Initialize({ barTexSize.x * -0.5f, barTexSize.y * -0.5f });
		sprite->SetTexHandle(barTex_);
		WorldTransform wt;
		wt.Initialize();
		const float kScale = 0.25f;
		wt.transform.scale = { kScale / 2.0f,kScale / 2.0f,1.0f };
		float angle = float(i) * 2.0f * float(numbers::pi) / float(BarMax) - float(numbers::pi) / 2.0f;

		wt.transform.rotate.z = angle + float(numbers::pi) / 2.0f;
		wt.transform.translate.x = center.x + radius * cos(angle);
		wt.transform.translate.y = center.y + radius * sin(angle);

		barSprites_[i] = move(sprite);
		barWts_[i] = move(wt);
	}

	for (auto& wt : flameWts_)
	{
		wt.UpdateMatrix();
	}

	for (auto& wt : barWts_)
	{
		wt.UpdateMatrix();
	}

	numberWorldTransform_.UpdateMatrix();
	backFlameWt_.UpdateMatrix();

	easeOutExpoMax_.rotate.z = float(numbers::pi) * 2.0f;
	easeOutExpoMax_.scale.x = 1.0f;
	easeOutExpoMax_.scale.y = 1.0f;
	easeOutExpoMax_.scale.z = 1.0f;

}

void StartCount::Update()
{
	if (countUpdateFlag_)
	{
		return;
	}

	float flameMax = 1.0f;
	isNumberChange_ = false;

	NumberUpdate();

	BarUpdate();

	FlameUpdate();

	//flameが上限に達したとき
	if (numberAnimationFlame_ >= flameMax)
	{
		float adduv = 0.25f;
		numberAnimationFlame_ = 0.0f;
		barCount_ = 0;

		timerCount++;

		isNumberChange_ = true;
		numberSprite_->GetuvTranslate().x += adduv;
	}

	//時間が上限に行ったとき
	if (timerCount >= timerCountMax)
	{
		startFlag_ = true;
		countUpdateFlag_ = true;
		countDrawFlag_ = true;
	}

	for (auto& wt : flameWts_)
	{
		wt.UpdateMatrix();
	}

	for (auto& wt : barWts_)
	{
		wt.UpdateMatrix();
	}

	numberWorldTransform_.UpdateMatrix();
	backFlameWt_.UpdateMatrix();
}

void StartCount::Draw2d()
{
	if (countDrawFlag_)
	{
		return;
	}

	backFlameSprite_->Draw(backFlameWt_);

	for (size_t i = 0; i < flameSprites_.size(); i++)
	{
		flameSprites_[i]->Draw(flameWts_[i]);
	}

	for (size_t i = 0; i < barCount_; i++)
	{
		barSprites_[i]->Draw(barWts_[i]);
	}

	numberSprite_->Draw(numberWorldTransform_);
}

void StartCount::NumberUpdate()
{
	float addFlame = 1.0f / 60.0f;


	numberAnimationFlame_ += addFlame;
	numberWorldTransform_.transform.rotate.z = Math::Vector::easeOutExpo(easeOutExpoMin_.scale.x, easeOutExpoMax_.rotate.z, numberAnimationFlame_);

	numberWorldTransform_.transform.scale.x = Math::Vector::easeOutExpo(easeOutExpoMin_.scale.x, easeOutExpoMax_.scale.x, numberAnimationFlame_);
	numberWorldTransform_.transform.scale.y = Math::Vector::easeOutExpo(easeOutExpoMin_.scale.y, easeOutExpoMax_.scale.y, numberAnimationFlame_);
	numberWorldTransform_.transform.scale.z = Math::Vector::easeOutExpo(easeOutExpoMin_.scale.z, easeOutExpoMax_.scale.z, numberAnimationFlame_);

}

void StartCount::BarUpdate()
{
	if (numberAnimationFlame_ >= 1.0f / (BarMax + 1) * (barCount_ + 1))
	{
		barCount_++;
		if (barCount_ > BarMax)
		{
			barCount_ = 0;
		}
	}
}

void StartCount::FlameUpdate()
{
	for (size_t i = 0; i < 4; i++)
	{
		flameWts_[i].transform.translate.x = Math::Vector::easeOutExpo(startFlamePos_[i].x, endFlamePos_[i].x, numberAnimationFlame_);
		flameWts_[i].transform.translate.y = Math::Vector::easeOutExpo(startFlamePos_[i].y, endFlamePos_[i].y, numberAnimationFlame_);
	}
}
