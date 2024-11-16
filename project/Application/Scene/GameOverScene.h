#pragma once

#include"Cleyera.h"
#include"GameManager.h"

#include"ChangeSceneAnimation/ChangeSceneAnimation.h"
#include"GameFileLoader/SceneFileLoder/SceneFileLoader.h"
#include"GameFileLoader/RailLoader/RailLoader.h"

#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/GameCollider/BoxCollisionManager.h"

#include"GameObject/Block/BlockManager.h"
#include"GameObject/GravityManager/GravityManager.h"
#include"GameObject/Player/PlayerManager.h"
#include"GameObject/EnemyWalk/EnemyWalkManager.h"
#include"GameObject/Goal/Goal.h"


#include"GameObject/Particles/CharacterDeadParticle.h"
#include"GameObject/Particles/CharacterMoveParticle.h"


#include"GameObject/GameOverText/GameOverText.h"
#include"GameObject/GameOverUI/GameOverUIManager.h"

#include"TitleScene.h"
#include"GameScene.h"
#include"SelectScene.h"


/// <summary>
/// ゲームオーバー
/// </summary>
class GameOverScene :public IScene
{
public:
	GameOverScene() {};
	~GameOverScene() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="Scene"></param>
	void Update([[maybe_unused]] GameManager* Scene)override;

	/// <summary>
	/// ポストエフェクトをかける
	/// </summary>
	void PostProcessDraw();

	/// <summary>
	/// 前景2d
	/// </summary>
	void Flont2dSpriteDraw();

private:

	shared_ptr<LevelData> levelData_ = nullptr;
	GameObjectManager* gameObjectManager_;

	string inputLevelDataFileName_ = "GameOver.json";

	PointLight_param light_{};

	unique_ptr<GameOverText>gameOverText_ = nullptr;
	unique_ptr<GameOverUIManager>gameOverUiManager_ = nullptr;
	ChangeSceneAnimation* changeSceneAnimation_ = nullptr;
};
