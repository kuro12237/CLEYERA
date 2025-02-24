#pragma once
#include "GameScene.h"
#include "GameScene/GameSceneEndState.h"
#include "IGameSceneState.h"
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
   void ImGuiUpdate() override;
 private:
   ChangeSceneAnimation *changeSceneAnimation_ = nullptr;

   // anim
   unique_ptr<StartAnimation> startAnimation_ = nullptr;
   // ui
   unique_ptr<GameSceneUI> gameUi_ = nullptr;

   weak_ptr<PlayerManager> playerManager_;
};
