#include "GameScenePlayState.h"

void GameScenePlayState::Initialize([[maybe_unused]] GameScene *scene)
{
   playerManager_ = scene->GetPlayerManager();

   gameUi_ = make_unique<GameSceneUI>();
   gameUi_->Initialize();
}

void GameScenePlayState::Update([[maybe_unused]] GameScene *scene)
{
   gameUi_->Update();

   auto core = playerManager_.lock()->GetPlayerCore();
   core->CheckStatePush<PlayerStateDeadAnimation>();
   core->CheckStatePush<PlayerStateGoalAnimation>();
   if (core->IsCheckStateRetuen()) {
      scene->ChangeGameSceneState(make_unique<GameSceneEndState>());
   }
}

void GameScenePlayState::Draw2d()
{

   playerManager_.lock()->Draw2d();
   playerManager_.lock()->Draw2dBullet();
   playerManager_.lock()->DrawHp();
   gameUi_->Draw2d();
}

void GameScenePlayState::ImGuiUpdate()
{
   gameUi_->ImGuiUpdate();
}
