#include "GameSceneEndState.h"

void GameSceneEndState::Initialize([[maybe_unused]]GameScene *scene)
{
   changeSceneAnimation_ = ChangeSceneAnimation::GetInstance();

   scene->SetIsGameStartFlag(false);
   endAnimation_ = make_unique<EndAnimation>();
   endAnimation_->Initialize();
}

void GameSceneEndState::Update(GameScene *scene) 
{
   endAnimation_->Update();
   if (scene->GetIsGameEnd())
   {
      endAnimation_->SetIsCountStart(true);
   }

   if (endAnimation_->GetCompleteFlag()) {
      changeSceneAnimation_->ChangeStart();
   }

}

void GameSceneEndState::Draw2d() {}