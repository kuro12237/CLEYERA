#pragma once

#include "Cleyera.h"
#include "GameManager.h"

#include "ChangeSceneAnimation/ChangeSceneAnimation.h"
#include "GameFileLoader/SceneFileLoder/SceneFileLoader.h"

#include "GameObject/GameCollider/BoxCollisionManager.h"
#include "GameObject/GravityManager/GravityManager.h"

#include "GameObject/Block/BlockManager.h"
#include "GameObject/EnemyWalk/EnemyWalkManager.h"
#include "GameObject/Player/PlayerManager.h"

#include "GameObject/Particles/CharacterDeadParticle.h"

#include "GameObject/Arch/Arch.h"
#include "GameObject/Bridge/Bridge.h"
#include "GameObject/Lava/Lava.h"
#include "GameObject/TitleCamera/TitleCamera.h"
#include "GameObject/TitleLight/TitleLight.h"
#include "GameObject/TitleName/TitleName.h"
#include "GameObject/TowerManager/TowerManager.h"

#include "GameObject/Particles/TitleNameParticle/TitleNameParticle.h"
#include "GameObject/StageManager/StageManager.h"
#include "GameObject/UI/TitleSceneUI/TitleSceneUI.h"

/// <summary>
/// タイトル
/// </summary>
class TitleScene : public IScene, public JsonComponent
{
public:
  TitleScene() {};
  ~TitleScene() {};

  /// <summary>
  /// 初期化
  /// </summary>
  void Initialize(GameManager *state) override;

  /// <summary>
  /// 更新
  /// </summary>
  void Update([[maybe_unused]] GameManager *Scene) override;

  void ImGuiUpdate() override;

  /// <summary>
  /// ポストエフェクト描画
  /// </summary>
  void PostProcessDraw()override;

  /// <summary>
  /// 前面2d描画
  /// </summary>
  void Flont2dSpriteDraw()override;

private:
  /// <summary>
  /// .000形式に変換する関数
  /// </summary>
  std::string FormatNumberWithDots(int num);

  shared_ptr<LevelData> levelData_ = nullptr;
  ChangeSceneAnimation *changeSceneAnimation_ = nullptr;
  StageManager *stageManager_ = nullptr;

  SkyBox *skyBox_ = nullptr;
  const float kSkyBoxScale_ = 256.0f;
  const Math::Vector::Vector3 *p_LavaPos_ = nullptr;

  string levelDataName_ = "TitleScene.json";

  unique_ptr<TitleCamera> camera_ = nullptr;
  unique_ptr<Arch> arch_ = nullptr;
  size_t bridgeSizeMax_ = 2;
  vector<unique_ptr<Bridge>> bridge_ = {};
  unique_ptr<TitleLight> titleLight_ = nullptr;
  unique_ptr<Lava> lava_ = nullptr;
  unique_ptr<TowerManager> towerManager_ = nullptr;
  unique_ptr<GravityManager> gravityManager_ = nullptr;

  unique_ptr<TitleName> titleName_ = nullptr;

  unique_ptr<ISceneUI> ui_ = nullptr;

#pragma region Particle

  unique_ptr<TitleNameParticle> titleNameParticle_ = nullptr;

#pragma endregion

  float flame_ = 0.0f;

  bool isChangeSelectScene_ = false;

  bool isAnimationStart_ = false;
  bool isAnimationEnd_ = false;

  const Math::Vector::Vector3 *p_CameraPos_ = nullptr;
};
