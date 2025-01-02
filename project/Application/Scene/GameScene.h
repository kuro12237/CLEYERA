#pragma once

#include"Cleyera.h"
#include"GameManager.h"

#include"GameObject/GameCollider/BoxCollisionManager.h"
#include"GameObject/GravityManager/GravityManager.h"

#include"GameObject/Block/BlockManager.h"
#include"GameObject/BreakBlock/BreakBlockManager.h"
#include"GameObject/EnemyWalk/EnemyWalkManager.h"
#include"GameObject/Warp/WarpManager.h"
#include"GameObject/Player/PlayerManager.h"
#include"GameObject/StageCoin/StageCoinManager.h"
#include"GameObject/GunEnemy/GunEnemyManager.h"

#include"GameObject/Goal/Goal.h"
#include"GameObject/Lava/Lava.h"

#include"GameObject/Particles/CharacterDeadParticle.h"
#include"GameObject/Particles/CharacterMoveParticle.h"


#include"GameObject/UI/GameSceneUI/GameSceneUI.h"

#include"GameFileLoader/RailLoader/RailLoader.h"

#include"ChangeSceneAnimation/ChangeSceneAnimation.h"
#include"GameObject/GameSceneAnimation/StartAnimation/StartAnimation.h"
#include"GameObject/GameSceneAnimation/GameOverAnimation/EndAnimation.h"

#include"GameObject/SceneContextData/SceneContextData.h"

#include"Scene/GameClearScene.h"
#include"Scene/TitleScene.h"

#include"ISceneContext.h"
#include"GameObject/ObjectInterface/IManagerList.h"

/// <summary>
/// ゲームプレイ
/// </summary>
class GameScene :public IScene
{
public:
	GameScene() {};
	~GameScene() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(GameManager* state)override;

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="Scene"></param>
	void Update([[maybe_unused]] GameManager* Scene)override;

private:
	/// <summary>
	/// ポストエフェクトをかける
	/// </summary>
	void PostProcessDraw();


	/// <summary>
	/// 前景2d
	/// </summary>
	void Flont2dSpriteDraw();

	/// <summary>
	/// Imguiの更新
	/// </summary>
	void ImGuiUpdate();

	/// <summary>
	/// 当たり判定
	/// </summary>
	void Collision();

	/// <summary>
	/// 重力
	/// </summary>
	void Gravitys();

	/// <summary>
	/// オブジェクトの更新
	/// </summary>
	void PlayUpdate();

#pragma region Particle
	void ParticlesInitialize();
	void ParticlesUpdate();
	void ParticlesDraw();
	void ParticleImGuiUpdate();
#pragma endregion


	GameObjectManager* gameObjectManager_;
	string inputLevelDataFileName_ = "LevelData_1.json";

	unique_ptr<ISceneContext>context_ = nullptr;
	SceneContextData contextData_ = {};

	list<IManagerList*>managerList_;


	CharacterDeadParticle* characterDeadParticle_ = nullptr;
	CharacterMoveParticle* characterMoveParticle_ = nullptr;

	Engine::Light::PointLight_param light_{};

	unique_ptr<PlayerManager>player_ = nullptr;

	unique_ptr<Goal>goal_ = nullptr;

	unique_ptr<EnemyWalkManager>enemyWalkManager_ = nullptr;
	unique_ptr<GunEnemyManager>bulletEnemyManager_ = nullptr;

	unique_ptr<WarpManager>warpManager_ = nullptr;
	shared_ptr<BlockManager>blockManager_ = nullptr;
	unique_ptr<BreakBlockManager>breakBlockManager_ = nullptr;
	unique_ptr<StageCoinManager>stageCoinManager_ = nullptr;

	unique_ptr<GravityManager>gravityManager_ = nullptr;
	unique_ptr<BoxCollisionManager>gameCollisionManager_ = nullptr;

	unique_ptr<GameSceneUI>gameUi_ = nullptr;

	unique_ptr<StartAnimation>startAnimation_ = nullptr;
	unique_ptr<EndAnimation>endAnimation_ = nullptr;

	unique_ptr<Lava>lava_ = nullptr;
	bool* isGameEnd_ = nullptr;
};
