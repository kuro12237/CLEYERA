#pragma once

#include"IScene.h"
#include"GameManager.h"
#include"Input.h"
#include"PostEffect/PostEffect.h"
#include"Game3dObject.h"
#include"TestScene.h"
#include"DebugTool/DebugCamera/DebugCamera.h"
#include"PostEffect/DeferrdShading/DeferredShading.h"
#include"Animation/AnimationManager.h"
#include"DebugTool/DebugSkeleton/DebugSkeleton.h"
#include"Model/primitive/Line.h"
#include"PostEffect/DeferrdShading/DeferredShading.h"
#include"SceneFileLoder/SceneFileLoader.h"

#include"GameObject/ObjectManager/GameObjectManager.h"
#include"GameObject/GameCollider/BoxCollisionManager.h"

#include"GameObject/Player/Player.h"
#include"GameObject/EnemyWalk/EnemyWalk.h"
#include"GameObject/Block/BlockManager.h"
#include"GameObject/GravityManager/GravityManager.h"
#include"GameObject/Player/PlayerManager.h"

class TestLevelDataScene :public IScene
{
public:
	TestLevelDataScene() {};
	~TestLevelDataScene() {};

	void Initialize()override;

	void Update(GameManager* Scene)override;

	void PostProcessDraw()override;

	void Back2dSpriteDraw()override;

	void Object3dDraw()override;

	void Flont2dSpriteDraw()override;

private:

	void Collision();

	void Gravitys();

	CameraData camera_{};
	unique_ptr<DebugCamera>debugCamera_ = nullptr;

	unique_ptr<PostEffect>postEffect_ = nullptr;

	unique_ptr<LevelData> levelData_ = nullptr;

	unique_ptr<GameObjectManager>objectManager_ = nullptr;
	unique_ptr<BoxCollisionManager>gameCollisionManager_ = nullptr;


	PointLight_param light_{};

	unique_ptr<PlayerCommandHandler>commandHandler_ = nullptr;

	unique_ptr<PlayerManager>player_ = nullptr;

	shared_ptr<EnemyWalk>enemyWalk_ = nullptr;
	shared_ptr<BlockManager>blockManager_ = nullptr;
	shared_ptr<GravityManager>gravityManager_ = nullptr;
};
