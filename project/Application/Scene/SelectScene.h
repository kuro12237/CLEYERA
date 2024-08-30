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

#include"ChangeSceneAnimation/ChangeSceneAnimation.h"
#include"GameObject/Goal/Goal.h"

class SelectScene :public IScene
{
public:
	SelectScene() {};
	~SelectScene() {};

	void Initialize()override;

	void Update([[maybe_unused]] GameManager* Scene)override;

	void PostProcessDraw()override;

	void Back2dSpriteDraw()override;

	void Object3dDraw()override;

	void Flont2dSpriteDraw()override;

private:

	void Collision();

	void Gravitys();

	bool CheckLoadScene();

	CameraData camera_ = {};

	shared_ptr<LevelData> levelData_ = nullptr;
	GameObjectManager* gameObjectManager_;
	string inputLevelDataFileName_ = "SelectSceneData.json";

	PointLight_param light_{};

	unique_ptr<PlayerManager>player_ = nullptr;

	uint32_t portalMax_ = 5;
	vector<shared_ptr<Goal>>goals_;


	shared_ptr<BlockManager>blockManager_ = nullptr;
	unique_ptr<GravityManager>gravityManager_ = nullptr;
	unique_ptr<BoxCollisionManager>gameCollisionManager_ = nullptr;
	CharacterDeadParticle* characterDeadParticle_ = nullptr;
	CharacterMoveParticle* characterMoveParticle_ = nullptr;

	bool* isGameEnd_ = nullptr;
};
