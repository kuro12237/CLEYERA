#include "GameSceneBottonsAction.h"

void GameSceneUIBottonsAction::Initialize()
{
	bottonA_ = make_unique<GameSceneUIBottonA>();
}

void GameSceneUIBottonsAction::BottonAActive(BaseBottonUI& ui)
{
	bottonA_->Active(ui);
}

void GameSceneUIBottonsAction::BottonAInactive(BaseBottonUI& ui)
{
	bottonA_->Inactive(ui);
}
