#pragma once
#include "IGameSceneState.h"
#include "GameScene.h"

#include"GameScenePlayState.h"

/// <summary>
/// 開始
/// </summary>
class GameSceneStartState : public IGameSceneState
{
 public:
   GameSceneStartState() {};
   ~GameSceneStartState() {};
   void Initialize(GameScene *scene) override;
   void Update(GameScene *scene) override;
   void Draw2d() override;
 private:
   // anim
   unique_ptr<StartAnimation> startAnimation_ = nullptr;

   ChangeSceneAnimation *changeSceneAnimation_ = nullptr;
};
