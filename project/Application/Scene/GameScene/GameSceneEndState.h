#pragma once
#include "GameScene.h"
#include "IGameSceneState.h"

/// <summary>
/// 終わり
/// </summary>
class GameSceneEndState : public IGameSceneState
{
 public:
   GameSceneEndState() {};
   ~GameSceneEndState() {};
   void Initialize(GameScene *scene) override;
   void Update(GameScene *scene) override;
   void Draw2d() override;

 private:
   // anim
   unique_ptr<EndAnimation> endAnimation_ = nullptr;

   weak_ptr<PlayerManager> playerManager_;

   

   ChangeSceneAnimation *changeSceneAnimation_ = nullptr;
};
