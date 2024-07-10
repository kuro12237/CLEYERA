#pragma once

#include"IScene.h"
#include"GameManager.h"
#include"Input.h"
#include"PostEffect/PostEffect.h"
#include"Game3dObject.h"
#include"DebugTool/DebugCamera/DebugCamera.h"
#include"Animation/AnimationManager.h"
#include"DebugTool/DebugSkeleton/DebugSkeleton.h"
#include"Model/primitive/Line.h"
#include"SceneFileLoder/SceneFileLoader.h"

#include"GameObject/ObjectManager/GameObjectManager.h"
#include"GameObject/GameCollider/BoxCollisionManager.h"

#include"GameObject/EnemyWalk/EnemyWalkManager.h"
#include"GameObject/Block/BlockManager.h"
#include"GameObject/GravityManager/GravityManager.h"
#include"GameObject/Player/PlayerManager.h"

class GameScene :public IScene
{
public:
	GameScene() {};
	~GameScene() {};

	void Initialize()override;

	void Update(GameManager* Scene)override;

	void PostProcessDraw()override;

	void Back2dSpriteDraw()override;

	void Object3dDraw()override;

	void Flont2dSpriteDraw()override;

private:

	void Collision();

	void Gravitys();

	GameObjectManager* gameObjectManager_;

	CameraData camera_{};
	unique_ptr<DebugCamera>debugCamera_ = nullptr;

	unique_ptr<PostEffect>postEffect_ = nullptr;

	shared_ptr<LevelData> levelData_ = nullptr;

	unique_ptr<BoxCollisionManager>gameCollisionManager_ = nullptr;

	PointLight_param light_{};

	unique_ptr<PlayerCommandHandler>commandHandler_ = nullptr;

	unique_ptr<PlayerManager>player_ = nullptr;
	shared_ptr<BlockManager>blockManager_ = nullptr;
	shared_ptr<GravityManager>gravityManager_ = nullptr;

	unique_ptr<EnemyWalkManager>enemyWalkManager_ = nullptr;


};
