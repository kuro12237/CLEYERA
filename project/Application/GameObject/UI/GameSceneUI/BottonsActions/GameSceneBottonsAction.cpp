#include "GameSceneBottonsAction.h"

void GameSceneUIBottonsAction::Initialize()
{
	bottonA_ = make_unique<GameSceneUIBottonA>();
	bottonRT_ = make_unique<GameSceneUIBottonRT>();
	bottonRB_ = make_unique<GameSceneUIBottonRB>();

	for (size_t i = 0; i < joystickMax_; i++)
	{
		joySticks_[i] = make_unique<GameSceneJoyStick>();
	}
}

void GameSceneUIBottonsAction::BottonAActive(BaseBottonUI& ui)
{
	bottonA_->Active(ui);
}

void GameSceneUIBottonsAction::BottonAInactive(BaseBottonUI& ui)
{
	bottonA_->Inactive(ui);
}

void GameSceneUIBottonsAction::BottonRTActive(BaseBottonUI& ui)
{
	bottonRT_->Active(ui);
}

void GameSceneUIBottonsAction::BottonRTInactive(BaseBottonUI& ui)
{
	bottonRT_->Inactive(ui);
}

void GameSceneUIBottonsAction::BottonRBActive(BaseBottonUI& ui)
{
	
	bottonRB_->Active(ui);
}

void GameSceneUIBottonsAction::BottonRBInactive(BaseBottonUI& ui)
{

	bottonRB_->Inactive(ui);
}

void GameSceneUIBottonsAction::JoyStickRInitialize(BaseBottonUI& ui)
{
	ui;
	//joySticks_[static_cast<uint32_t>(SceneUIEnum::JoyStick_R)]->Initialize();
}

void GameSceneUIBottonsAction::JoyStickRUpdate(BaseBottonUI& ui)
{

	joySticks_[static_cast<uint32_t>(SceneUIEnum::JoyStick_R)]->Update(ui);
}

void GameSceneUIBottonsAction::JoyStickLInitialize(BaseBottonUI& ui)
{
	ui;
	//joySticks_[static_cast<uint32_t>(SceneUIEnum::JoyStick_L)]->Initialize(ui);
}

void GameSceneUIBottonsAction::JoyStickLUpdate(BaseBottonUI& ui)
{
	joySticks_[static_cast<uint32_t>(SceneUIEnum::JoyStick_L)]->Update(ui);
}
