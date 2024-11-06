#include "GameSceneBottonsAction.h"

void GameSceneUIBottonsAction::Initialize()
{
	bottonA_ = make_unique<GameSceneUIBottonA>();
	bottonRT_ = make_unique<GameSceneUIBottonRT>();
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
