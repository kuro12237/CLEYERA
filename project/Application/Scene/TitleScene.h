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

#include"GameObject/Particles/CharacterDeadParticle.h"

#include"ChangeSceneAnimation/ChangeSceneAnimation.h"

#include"TitleObject/TitleCamera/TitleCamera.h"
#include"TitleObject/Arch/Arch.h"
#include"TitleObject/Bridge/Bridge.h"
#include"TitleObject/TitleLight/TitleLight.h"
#include"TitleObject/Lava/Lava.h"
#include"TitleObject/TitleName/TitleName.h"

class TitleScene:public IScene
{
public:
	TitleScene() {};
	~TitleScene() {};

	void Initialize()override;

	void Update([[maybe_unused]] GameManager* Scene)override;

	void PostProcessDraw()override;

	void Back2dSpriteDraw()override;

	void Object3dDraw()override;

	void Flont2dSpriteDraw()override;

private:
	
	/// <summary>
	/// .001Œ`Ž®‚Å•Ô‚·
	/// </summary>
	std::string FormatNumberWithDots(int num);

	shared_ptr<LevelData> levelData_ = nullptr;
	GameObjectManager* gameObjectManager_ = nullptr;
	ChangeSceneAnimation* changeSceneAnimation_ = nullptr;
	SkyBox* skyBox_ = nullptr;
	const float kSkyBoxScale_ = 256.0f;

	string levelDataName_ = "TitleScene.json";


	unique_ptr<TitleCamera>camera_ = nullptr;
	unique_ptr<Arch>arch_ = nullptr;
	size_t bridgeSizeMax_ = 2;
	vector<unique_ptr<Bridge>>bridge_ = {};
	unique_ptr<TitleLight>titleLight_ = nullptr;
	unique_ptr<Lava>lava_ = nullptr;

	unique_ptr<TitleName>titleName_ = nullptr;

	bool isChangeSelectScene_ = false;

	bool isAnimationStart_ = false;
	bool isAnimationEnd_ = false;

	const Math::Vector::Vector3 *p_CameraPos_ = nullptr;
};
