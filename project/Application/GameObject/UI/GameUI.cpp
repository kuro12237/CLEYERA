#include "GameUI.h"

void GameUI::Initialize()
{
	bottonATexhandle_ = TextureManager::LoadDDSTexture("GameObject/ControlUI/A_botton_UI.dds");
	bottonASprite_ = make_unique<Sprite>();
	bottonASprite_->Initialize();
	bottonASprite_->SetTexHandle(bottonATexhandle_);
	bottonAwT_.Initialize();
}

void GameUI::Update()
{
	bottonAwT_.UpdateMatrix();
}

void GameUI::Draw2d()
{
	bottonASprite_->Draw(bottonAwT_);
}
