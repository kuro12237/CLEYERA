#include "GameOverUIManager.h"

using namespace Engine::Base::Win;
using namespace Engine::Objects;

using namespace Engine;
using namespace Engine::Manager;
using namespace Engine::Transform;

void GameOverUIManager::Initialize()
{
	uiPos_.x = 0.0f;
	uiPos_.y = 360.0f;

	for (size_t i = 0; i < uiMax_; i++)
	{
		gameOverUIs_[i] = make_unique<GameOverUI>();
		gameOverUIs_[i]->SetSelectIndex(uint32_t(i + 1));
		gameOverUIs_[i]->Initialize();

		//ƒ|ƒWƒVƒ‡ƒ“Ý’è
		Math::Vector::Vector3 translate = { gameOverUIs_[i]->GetTexSize().x * 0.25f,gameOverUIs_[i]->GetTexSize().y * 0.25f,0.0f };
		translate.x = translate.x * static_cast<float>(i + 1) + 128.0f * static_cast<float>(i);
		translate.y += uiPos_.y;

		gameOverUIs_[i]->SetTranslate(translate);

		uiBackWorldTransform_[i] = &gameOverUIs_[i]->GetWorldTransform();
	}


	uiBackSprite_ = make_unique<Sprite>();
	uiBackTexhandle_ = TextureManager::LoadPngTexture("GameOverSelectUI/uiback.png");
	Math::Vector::Vector2 texPos = TextureManager::GetTextureSize(uiBackTexhandle_);
	texPos.x *= -0.5f;
	texPos.y *= -0.5f;
	uiBackSprite_->Initialize(texPos);
	uiBackSprite_->SetTexHandle(uiBackTexhandle_);
	uiBackSprite_->SetColor({ 1.0f,1.0f,1.0f,0.5f });

	gameOverActiveparticle_ = make_unique<GameOverActiveUIParticle>();
	gameOverActiveparticle_->Initialize();



}

void GameOverUIManager::Update()
{
	flame_ += 1.0f / 20.0f;
	if (!isSelect_)
	{
		if (flame_ >= flameMax_)
		{
			if (IsLJoystickActive())
			{
				if (Input::GetJoyLStickPos().x >= 0.2f)
				{
					selectIndex_++;
				}
				if (Input::GetJoyLStickPos().x <= -0.2f)
				{
					selectIndex_--;
				}
				flame_ = 0.0f;
			}
		}
	}

	if (selectIndex_ < selectIndexMin_)
	{
		selectIndex_ = selectIndexMax_;
	}
	if (selectIndex_ > selectIndexMax_)
	{
		selectIndex_ = selectIndexMin_;
	}
	
	if (Input::PushBottonPressed(XINPUT_GAMEPAD_A))
	{
		isSelect_ = true;
	}

	for (size_t i = 0; i < uiMax_; i++)
	{
		if (selectIndex_ == i)
		{
			gameOverUIs_[i]->SetIsSelect(true);
			gameOverActiveparticle_->SetEmitParam(gameOverUIs_[i]->GetWorldTransform().transform.translate);
		}
		else
		{
			gameOverUIs_[i]->SetIsSelect(false);
		}

		gameOverUIs_[i]->Update();
	}


	gameOverActiveparticle_->Update();

}

void GameOverUIManager::Draw2d()
{
	gameOverActiveparticle_->Draw();
	for (size_t i = 0; i < uiMax_; i++)
	{
		uiBackSprite_->Draw(*uiBackWorldTransform_[i]);
		gameOverUIs_[i]->Draw2d();
	}
}

bool GameOverUIManager::IsLJoystickActive()
{

	float joystickThreshold = 0.2f;
	Math::Vector::Vector2 Ljoy = Input::GetInstance()->GetJoyLStickPos();
	if (std::abs(Ljoy.x) > joystickThreshold || std::abs(Ljoy.y) > joystickThreshold) {

		return true;
	}
	return false;
}