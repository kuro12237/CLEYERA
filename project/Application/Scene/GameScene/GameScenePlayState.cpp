#include "GameScenePlayState.h"

void GameScenePlayState::Initialize([[maybe_unused]] GameScene *scene)
{
   playerManager_ = scene->GetPlayerManager();
}

void GameScenePlayState::Update([[maybe_unused]] GameScene *scene) 
{
   auto core = playerManager_.lock()->GetPlayerCore();
   core->CheckStatePush<PlayerStateDeadAnimation>();
   core->CheckStatePush<PlayerStateGoalAnimation>();
   if (core->IsCheckStateRetuen())
   {
      scene->ChangeGameSceneState(nullptr);
   }
}

void GameScenePlayState::Draw2d() {}
