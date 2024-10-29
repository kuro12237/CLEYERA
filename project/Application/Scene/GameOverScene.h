#pragma once

#include"IScene.h"
#include"GameManager.h"
#include"Input.h"
#include"PostEffect/PostEffect.h"
#include"Game3dObject.h"
#include"Animation/AnimationManager.h"
#include"DebugTool/DebugSkeleton/DebugSkeleton.h"
#include"Model/primitive/LineModel.h"
#include"GameFileLoader/SceneFileLoder/SceneFileLoader.h"


#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/GameCollider/BoxCollisionManager.h"

#include"GameObject/Block/BlockManager.h"
#include"GameObject/GravityManager/GravityManager.h"
#include"GameObject/Player/PlayerManager.h"
#include"GameObject/EnemyWalk/EnemyWalkManager.h"
#include"GameObject/Goal/Goal.h"


#include"GameObject/Particles/CharacterDeadParticle.h"
#include"GameObject/Particles/CharacterMoveParticle.h"

#include"ChangeSceneAnimation/ChangeSceneAnimation.h"
#include"Particle/Field/ParticleField.h"

#include"GameObject/UI/GameUI.h"

#include"Scene/TitleScene.h"
#include"GameFileLoader/RailLoader/RailLoader.h"


#include"Light/LightingManager.h"

#include"TitleScene.h"
#include"GameScene.h"
#include"SelectScene.h"

#include"GameObject/GameOverText/GameOverText.h"
#include"GameObject/GameOverUI/GameOverUIManager.h"

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
	void PostProcessDraw()override;

	/// <summary>
	/// 後背景
	/// </summary>
	void Back2dSpriteDraw()override;

	/// <summary>
	/// objectDraw
	/// </summary>
	void Object3dDraw()override;

	/// <summary>
	/// 前景2d
	/// </summary>
	void Flont2dSpriteDraw()override;


private:

	shared_ptr<LevelData> levelData_ = nullptr;
	GameObjectManager* gameObjectManager_;

	string inputLevelDataFileName_ = "GameOver.json";

	PointLight_param light_{};

	unique_ptr<GameOverText>gameOverText_ = nullptr;
	unique_ptr<GameOverUIManager>gameOverUiManager_ = nullptr;
	ChangeSceneAnimation* changeSceneAnimation_ = nullptr;
};
