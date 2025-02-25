#pragma once

#include "Cleyera.h"
#include "GameManager.h"

#include "ChangeSceneAnimation/ChangeSceneAnimation.h"

#include "GameFileLoader/RailLoader/RailLoader.h"
#include "GameFileLoader/SceneFileLoder/SceneFileLoader.h"

#include "GameObject/GameCollider/BoxCollisionManager.h"
#include "GameObject/GravityManager/GravityManager.h"

#include "GameObject/Block/BlockManager.h"
#include "GameObject/EnemyWalk/EnemyWalkManager.h"
#include "GameObject/Goal/Goal.h"
#include "GameObject/Player/PlayerManager.h"

#include "GameObject/Particles/CharacterDeadParticle.h"
#include "GameObject/Particles/CharacterMoveParticle.h"

#include "GameScene.h"
#include "SelectScene.h"
#include "TitleScene.h"

#include "GameObject/UI/ClearSceneUI/ClearSceneUI.h"

#include "GameObject/ClearCamera/ClearCamera.h"
#include "GameObject/ClearCharacter/ClearCharacter.h"
#include "GameObject/SceneContextData/SceneContextData.h"

#include "GameObject/ClearCoinManager/ClearCoinManager.h"
#include "GameObject/Particles/Explosion/ExplosionParticle.h"

/// <summary>
/// ゲームクリア
/// </summary>
class GameClearScene : public IScene, JsonComponent
{
 public:
   GameClearScene() {};
   ~GameClearScene() {};

   /// <summary>
   /// 初期化
   /// </summary>
   void Initialize(GameManager *state) override;

   /// <summary>
   /// 更新
   /// </summary>
   /// <param name="Scene"></param>
   void Update([[maybe_unused]] GameManager *Scene) override;

   void ImGuiUpdate() override;

   /// <summary>
   /// ポストエフェクトをかける
   /// </summary>
   void PostProcessDraw() override;

   /// <summary>
   /// 前景2d
   /// </summary>
   void Flont2dSpriteDraw() override;

 private:
   ChangeSceneAnimation *changeSceneAnimation_ = nullptr;

   string inputLevelDataFileName_ = "GameClear.json";

   Engine::Light::PointLight_param light_{};

   SceneContextData contextData_ = {};

   unique_ptr<ClearSceneUI> ui_ = nullptr;

   unique_ptr<ClearCharacter> character_ = nullptr;
   unique_ptr<ClearCoinManager> coinManager_ = nullptr;
   unique_ptr<ClearCamera> camera_ = nullptr;

   unique_ptr<Lava> lava_ = nullptr;
   unique_ptr<GravityManager> gravityManager_ = nullptr;

   unique_ptr<ExplosionParticle> explosionParticle_ = nullptr;
};
