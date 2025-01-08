#pragma once

#include"Cleyera.h"

#include"GameFileLoader/SceneFileLoder/SceneFileLoader.h"


#include"GameObject/GameCollider/BoxCollisionManager.h"
#include"GameObject/GravityManager/GravityManager.h"

#include"ChangeSceneAnimation/ChangeSceneAnimation.h"
#include"GameObject/EnemyWalk/EnemyWalkManager.h"
#include"GameObject/Block/BlockManager.h"
#include"GameObject/Player/PlayerManager.h"

#include"GameObject/StageManager/StageManager.h"

#include"GameObject/Goal/Goal.h"
#include"GameObject/Lava/Lava.h"

#include"GameScene.h"

#include"GameObject/SceneContextData/SceneContextData.h"
#include"GameObject/UI/SelectSceneUI/SelectSceneUI.h"

#include"GameObject/SelectStageNumber/StageNumber.h"

/// <summary>
/// MapSelect
/// </summary>
class SelectScene :public IScene
{
public:
	SelectScene() {};
	~SelectScene() {};

	void Initialize(GameManager* state)override;

	void Update([[maybe_unused]] GameManager* Scene)override;


private:
	void PostProcessDraw();

	void Flont2dSpriteDraw();

	void Collision();

	void Gravitys();

	bool CheckLoadScene();

	list<IObjectData*>objectDataList_;

	SceneContextData contextData_;
	unique_ptr<ISceneContext>context_ = nullptr;
	GameObjectManager* gameObjectManager_;
	string inputLevelDataFileName_ = "SelectSceneData.json";
	StageManager* stageManager_ = nullptr;

	Engine::Light::PointLight_param light_{};

	unique_ptr<PlayerManager>player_ = nullptr;

	uint32_t portalMax_ = 3;
	vector<shared_ptr<Goal>>goals_;


	shared_ptr<BlockManager>blockManager_ = nullptr;
	unique_ptr<GravityManager>gravityManager_ = nullptr;
	unique_ptr<BoxCollisionManager>gameCollisionManager_ = nullptr;
	unique_ptr<Lava>lava_ = nullptr;
	CharacterDeadParticle* characterDeadParticle_ = nullptr;
	
	unique_ptr<SelectSceneUI>ui_ = nullptr;

	vector<unique_ptr<StageNumber>>stageNumbers_;

	bool* isGameEnd_ = nullptr;
};
