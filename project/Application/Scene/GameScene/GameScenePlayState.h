#pragma once
#include "GameScene.h"
#include "IGameSceneState.h"
#include"GameScene/GameSceneEndState.h"
/// <summary>
/// play中
/// </summary>
class GameScenePlayState : public IGameSceneState
{
 public:
   GameScenePlayState() {};
   ~GameScenePlayState() {};
   void Initialize(GameScene *scene) override;
   void Update(GameScene *scene) override;
   void Draw2d() override;

 private:
   // anim
   unique_ptr<StartAnimation> startAnimation_ = nullptr;

   ChangeSceneAnimation *changeSceneAnimation_ = nullptr;

   weak_ptr<PlayerManager> playerManager_;
};
