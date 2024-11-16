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

/// <summary>
/// �Q�[���I�[�o�[
/// </summary>
class GameClearScene :public IScene
{
public:
	GameClearScene() {};
	~GameClearScene() {};

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

	shared_ptr<LevelData> levelData_ = nullptr;
	GameObjectManager* gameObjectManager_;

	string inputLevelDataFileName_ = "GameClear.json";

	PointLight_param light_{};

	//unique_ptr<GameOverText>gameOverText_ = nullptr;
	unique_ptr<ClearSceneUI>ui_ = nullptr;

	ChangeSceneAnimation* changeSceneAnimation_ = nullptr;
};
