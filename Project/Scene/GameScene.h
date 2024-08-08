#pragma once

#include"IScene.h"
#include"GameManager.h"
#include"Input.h"
#include"PostEffect/PostEffect.h"
#include"Game3dObject.h"
#include"DebugTool/DebugCamera/DebugCamera.h"
#include"PostEffect/DeferrdShading/DeferredShading.h"
#include"Animation/AnimationManager.h"
#include"DebugTool/DebugSkeleton/DebugSkeleton.h"
#include"Model/primitive/LineModel.h"
#include"PostEffect/DeferrdShading/DeferredShading.h"
#include"SceneFileLoder/SceneFileLoader.h"

#include"GameObject/ObjectManager/GameObjectManager.h"
#include"GameObject/GameCollider/BoxCollisionManager.h"

#include"GameObject/EnemyWalk/EnemyWalkManager.h"
#include"GameObject/Block/BlockManager.h"
#include"GameObject/GravityManager/GravityManager.h"
#include"GameObject/Player/PlayerManager.h"

#include"Utility/SkyBox/SkyBox.h"
#include"Particle/GpuParticle.h"
#include"Particle/Emitter/ParticleEmitter.h"

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

	shared_ptr<LevelData> levelData_ = nullptr;
	GameObjectManager* gameObjectManager_;

	unique_ptr<DebugCamera>debugCamera_ = nullptr;

	string inputLevelDataFileName_ = "LevelData_1.json";

	PointLight_param light_{};

	unique_ptr<PlayerManager>player_ = nullptr;

	unique_ptr<EnemyWalkManager>enemyWalkManager_ = nullptr;

	unique_ptr<Particle::GpuParticle>gpuParticle_ = nullptr;
	unique_ptr < Particle::ParticleEmitter < Particle::EmitType::BoxParam >> emitter_ = nullptr;

	shared_ptr<BlockManager>blockManager_ = nullptr;
	unique_ptr<GravityManager>gravityManager_ = nullptr;
	unique_ptr<BoxCollisionManager>gameCollisionManager_ = nullptr;
};
