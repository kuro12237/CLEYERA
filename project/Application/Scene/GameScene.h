#pragma once

#include"IScene.h"
#include"GameManager.h"
#include"Input.h"
#include"PostEffect/PostEffect.h"
#include"Game3dObject.h"
#include"DebugTool/DebugCamera/DebugCamera.h"
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

#include"GameObject/UI/GameSceneUI/GameSceneUI.h"

#include"Scene/TitleScene.h"
#include"GameFileLoader/RailLoader/RailLoader.h"

#include"GameObject/Warp/WarpManager.h"

#include"GameObject/GameSceneAnimation/StartAnimation/StartAnimation.h"
#include"GameObject/GameSceneAnimation/GameOverAnimation/EndAnimation.h"

/// <summary>
/// �Q�[���v���C
/// </summary>
class GameScene :public IScene
{
public:
	GameScene() {};
	~GameScene() {};

	/// <summary>
	/// ������
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="Scene"></param>
	void Update([[maybe_unused]] GameManager* Scene)override;

	/// <summary>
	/// �|�X�g�G�t�F�N�g��������
	/// </summary>
	void PostProcessDraw()override;

	/// <summary>
	/// ��w�i
	/// </summary>
	void Back2dSpriteDraw()override;

	/// <summary>
	/// objectDraw
	/// </summary>
	void Object3dDraw()override;

	/// <summary>
	/// �O�i2d
	/// </summary>
	void Flont2dSpriteDraw()override;

private:

	/// <summary>
	/// Imgui�̍X�V
	/// </summary>
	void ImGuiUpdate();

	/// <summary>
	/// �����蔻��
	/// </summary>
	void Collision();

	/// <summary>
	/// �d��
	/// </summary>
	void Gravitys();

#pragma region Particle
	void ParticlesInitialize();
	void ParticlesUpdate();
	void ParticlesDraw();
	void ParticleImGuiUpdate();
#pragma endregion


	shared_ptr<LevelData> levelData_ = nullptr;
	GameObjectManager* gameObjectManager_;
	string inputLevelDataFileName_ = "LevelData_1.json";

	PointLight_param light_{};

	unique_ptr<StartAnimation>startAnimation_ = nullptr;

	unique_ptr<PlayerManager>player_ = nullptr;

	unique_ptr<EnemyWalkManager>enemyWalkManager_ = nullptr;

	shared_ptr<BlockManager>blockManager_ = nullptr;
	unique_ptr<GravityManager>gravityManager_ = nullptr;
	unique_ptr<BoxCollisionManager>gameCollisionManager_ = nullptr;

	unique_ptr<Goal>goal_ = nullptr;

	CharacterDeadParticle* characterDeadParticle_ = nullptr;
	CharacterMoveParticle* characterMoveParticle_ = nullptr;

	unique_ptr<GameSceneUI>gameUi_ = nullptr;

	unique_ptr<WarpManager>warpManager_ = nullptr;


	unique_ptr<EndAnimation>endAnimation_ = nullptr;

	bool* isGameEnd_ = nullptr;
};
