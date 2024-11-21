#pragma once

#include"Cleyera.h"
#include"GameManager.h"

#include"ChangeSceneAnimation/ChangeSceneAnimation.h"

#include"GameFileLoader/RailLoader/RailLoader.h"
#include"GameFileLoader/SceneFileLoder/SceneFileLoader.h"

#include"GameObject/GameCollider/BoxCollisionManager.h"
#include"GameObject/GravityManager/GravityManager.h"

#include"GameObject/Block/BlockManager.h"
#include"GameObject/Player/PlayerManager.h"
#include"GameObject/EnemyWalk/EnemyWalkManager.h"
#include"GameObject/Goal/Goal.h"


#include"GameObject/Particles/CharacterDeadParticle.h"
#include"GameObject/Particles/CharacterMoveParticle.h"


#include"TitleScene.h"
#include"GameScene.h"
#include"SelectScene.h"

#include"GameObject/UI/ClearSceneUI/ClearSceneUI.h"

#include"GameObject/GameClear/GameClearText.h"

#include"GameObject/ClearCharacter/ClearCharacter.h"
#include"GameObject/ClearCamera/ClearCamera.h"

#include"GameObject/Particles/Fire/FireParticle.h"


/// <summary>
/// ゲームオーバー
/// </summary>
class GameClearScene :public IScene
{
public:
	GameClearScene() {};
	~GameClearScene() {};

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

	shared_ptr<LevelData> levelData_ = nullptr;
	GameObjectManager* gameObjectManager_;

	string inputLevelDataFileName_ = "GameClear.json";

	Engine::Light::PointLight_param light_{};

	unique_ptr<SceneContextData>context_ = nullptr;
	SceneContextData contextData_ = {};

	unique_ptr<ClearSceneUI>ui_ = nullptr;

	ChangeSceneAnimation* changeSceneAnimation_ = nullptr;

	unique_ptr<GameClearText>gaameClearText_ = nullptr;

	unique_ptr<ClearCharacter>character_ = nullptr;
	unique_ptr<ClearCamera>camera_ = nullptr;

	unique_ptr<FireParticle>fireParticle_ = nullptr;

};
