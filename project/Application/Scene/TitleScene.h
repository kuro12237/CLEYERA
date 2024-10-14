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
#include"GameFileLoader/SceneFileLoder/SceneFileLoader.h"

#include"Utility/ObjectManager/GameObjectManager.h"
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

#include"GameObject/TitleCamera/TitleCamera.h"
#include"GameObject/Arch/Arch.h"
#include"GameObject/Bridge/Bridge.h"
#include"GameObject/TitleLight/TitleLight.h"
#include"GameObject/Lava/Lava.h"
#include"GameObject/TitleName/TitleName.h"
#include"GameObject/TowerManager/TowerManager.h"
#include"GameObject/TitleUI/TitlePushA.h"
#include"GameObject/Particles/Fire/FireParticle.h"
#include"GameObject/Particles/FireEmber2d/FireEmber2Particle.h"


/// <summary>
/// タイトル
/// </summary>
class TitleScene :public IScene
{
public:
	TitleScene() {};
	~TitleScene() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update([[maybe_unused]] GameManager* Scene)override;

	/// <summary>
	/// ポストエフェクト描画
	/// </summary>
	void PostProcessDraw()override;

	/// <summary>
	/// 背景2d描画
	/// </summary>
	void Back2dSpriteDraw()override;

	/// <summary>
	/// 描画
	/// </summary>
	void Object3dDraw()override;

	/// <summary>
	/// 前面2d描画
	/// </summary>
	void Flont2dSpriteDraw()override;

private:

	/// <summary>
	/// .000形式に変換する関数
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
	unique_ptr<TowerManager>towerManager_ = nullptr;

	unique_ptr<TitleName>titleName_ = nullptr;
	//UI
	unique_ptr<TitlePushA>titlePushA_ = nullptr;

	unique_ptr<FireEmber2dParticle>fireEmberParticle_ = nullptr;

#pragma region Particle

	unique_ptr<FireParticle>fireParticle_ = nullptr;

#pragma endregion


	bool isChangeSelectScene_ = false;

	bool isAnimationStart_ = false;
	bool isAnimationEnd_ = false;

	const Math::Vector::Vector3* p_CameraPos_ = nullptr;
};
