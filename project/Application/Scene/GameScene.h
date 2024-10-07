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

#include"GameObject/Block/BlockManager.h"
#include"GameObject/GravityManager/GravityManager.h"
#include"GameObject/Player/PlayerManager.h"
#include"GameObject/EnemyWalk/EnemyWalkManager.h"
#include"GameObject/Goal/Goal.h"

#include"GameObject/StartCount/StartCount.h"

#include"GameObject/Particles/CharacterDeadParticle.h"
#include"GameObject/Particles/CharacterMoveParticle.h"

#include"ChangeSceneAnimation/ChangeSceneAnimation.h"
#include"Particle/Field/ParticleField.h"

#include"GameObject/UI/GameUI.h"
#include"Scene/TitleScene.h"

class GameScene :public IScene
{
public:
	GameScene() {};
	~GameScene() {};

	void Initialize()override;

	void Update([[maybe_unused]] GameManager* Scene)override;

	void PostProcessDraw()override;

	void Back2dSpriteDraw()override;

	void Object3dDraw()override;

	void Flont2dSpriteDraw()override;

private:

	void ImGuiUpdate();

	void Collision();

	void Gravitys();

	void ParticlesInitialize();
	void ParticlesUpdate();
	void ParticlesDraw();

	void ParticleImGuiUpdate();

	shared_ptr<LevelData> levelData_ = nullptr;
	GameObjectManager* gameObjectManager_;
	string inputLevelDataFileName_ = "LevelData_1.json";

	PointLight_param light_{};

	unique_ptr<StartCount>startCount_ = nullptr;


	unique_ptr<PlayerManager>player_ = nullptr;

	unique_ptr<EnemyWalkManager>enemyWalkManager_ = nullptr;

	shared_ptr<BlockManager>blockManager_ = nullptr;
	unique_ptr<GravityManager>gravityManager_ = nullptr;
	unique_ptr<BoxCollisionManager>gameCollisionManager_ = nullptr;

	unique_ptr<Goal>goal_ = nullptr;

	CharacterDeadParticle* characterDeadParticle_ = nullptr;
	CharacterMoveParticle* characterMoveParticle_ = nullptr;

	unique_ptr<GameUI>gameUi_ = nullptr;


	bool* isGameEnd_ = nullptr;
};
