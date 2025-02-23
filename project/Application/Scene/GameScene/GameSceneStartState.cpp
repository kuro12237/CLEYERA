#include "GameSceneStartState.h"

void GameSceneStartState::Initialize([[maybe_unused]] GameScene *scene)
{
   changeSceneAnimation_ = ChangeSceneAnimation::GetInstance();

   startAnimation_ = make_unique<StartAnimation>();
   startAnimation_->Initialize(scene->GetSelectSceneContextData().stageNumber);
}

void GameSceneStartState::Update([[maybe_unused]] GameScene *scene)
{
   if (changeSceneAnimation_->GetIsComplite()) {
      startAnimation_->SetIsCountStart(true);
   }

   startAnimation_->Update();

   if (startAnimation_->GetIsGameStartFlag()) {
      scene->SetIsGameStartFlag(true);
      scene->ChangeGameSceneState(make_unique<GameScenePlayState>());
   }
}

void GameSceneStartState::Draw2d()
{
   startAnimation_->Draw2d();
}
