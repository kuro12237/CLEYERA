#include "GameSceneEndState.h"

void GameSceneEndState::Initialize([[maybe_unused]]GameScene *scene)
{
   changeSceneAnimation_ = ChangeSceneAnimation::GetInstance();

   playerManager_ = scene->GetPlayerManager();

   scene->SetIsGameStartFlag(false);
   endAnimation_ = make_unique<EndAnimation>();
   endAnimation_->Initialize();
}

void GameSceneEndState::Update([[maybe_unused]]GameScene *scene) 
{
   endAnimation_->Update();

   auto core = playerManager_.lock()->GetPlayerCore();

   //dead
   core->CheckStatePush<PlayerStateDeadAnimation>();
   if (core->IsCheckStateRetuen()) {
      if (core->GetIsDeadAnimationComplite())
      {
         changeSceneAnimation_->ChangeStart();
      }
   }

   //clear
   core->CheckStatePush<PlayerStateGoalAnimation>();
   if (core->IsCheckStateRetuen()) {

      changeSceneAnimation_->ChangeStart();
   }

}

void GameSceneEndState::Draw2d() {}