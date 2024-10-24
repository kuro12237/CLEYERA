#pragma once
#include"STransformEular.h"
#include"Pch.h"
#include"Input.h"
#include"PostEffect/PostEffect.h"

#include"Utility/DeltaTimer/DeltaTimer.h"

#include"Utility/ObjectId/GameObjectId.h"
#include"GameObject/ObjectInterface/IObjectData.h"
#include"GameObject/GameCollider/ICollider.h"

#include"command/PlayerCommandHandler.h"

#include"state/IPlayerState.h"
#include"state/PlayerStateNone.h"
#include"state/PlayerStateRock.h"
#include"state/PlayerStateGoalAnimation.h"
#include"state/PlayerStateWarpMove.h"

#include"Utility/ObjectManager/GameObjectManager.h"

#include"GameObject/Particles/CharacterMoveParticle.h"

/// <summary>
/// ���삷��Core�N���X
/// </summary>
class Player :public IObjectData, public ICollider
{
public:
	Player() {};
	~Player() {};

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ImGui�X�V
	/// </summary>
	void ImGuiUpdate();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// HP�̍X�V
	/// </summary>
	void HpUpdate();

	/// <summary>
	/// �����������̏���
	/// </summary>
	/// <param name="c"></param>
	void OnCollision(ICollider* c)override;

	/// <summary>
	/// ��ԑJ��
	/// </summary>
	/// <param name="newState"></param>
	void ChangeState(unique_ptr<IPlayerState>newState);

#pragma region Command

	/// <summary>
	/// JampCommand
	/// </summary>
	void Jamp();

	/// <summary>
	///�@MoveCommand
	/// </summary>
	/// <param name="speed"></param>
	void Move(float speed);

	/// <summary>
	/// �ˌ��R�}���h
	/// </summary>
	void Shoot();

	/// <summary>
	/// �ʒu��������
	/// </summary>
	void ResetPos() { gameObjectInstance_->GetObj3dData(name_)->GetWorldTransform().transform.translate = resetPos_; }
#pragma endregion

#pragma region Get
	bool GetIsJamp() { return isJamp_; }
	bool GetIsShoot() { return isShoot_; }
	bool& GetIsGameEnd() { return isGameEnd_; }
	bool GetIsGoal() { return isGoal_; }

	bool& isDamageFlag() { return isDamage_; }
	bool& isInvincible() { return isInvincible_; }
	string& GetWarpFilePath() { return warpFilePath_; }
	bool GetIsUseGravityFlag() { return isUseGravityFlag_; }
#pragma endregion

#pragma region Set
	void SetRockState(bool f) { isRockState_ = f; }
	void SetDamageFlag(bool f) { isDamage_ = f; }
	void SetIsUseGravityFlag(bool f) { isUseGravityFlag_ = f; }
#pragma endregion

private:

	/// <summary>
	/// �_���[�W�X�V
	/// </summary>
	void DamageUpdate();

	/// <summary>
	/// �R���g���[���[�̃f�b�h�]�[��
	/// </summary>
	/// <param name="v"></param>
	void ControlDeadZone(Math::Vector::Vector2& v);

	unique_ptr<IPlayerState>state_ = nullptr;

	//singleton
	GameObjectManager* gameObjectInstance_ = nullptr;

	bool isJamp_ = false;
	bool isShoot_ = false;
	bool isRockState_ = false;
	bool isDamage_ = false;

	bool isInvincible_ = false;
	bool isGameEnd_ = false;
	bool isGoal_ = false;

	float damegeFlame_ = 0.0f;
	uint32_t damegeCoolTimer_ = 0;
	uint32_t damageCoolTimerMax_ = 2;

	float vinatteFactor_ = 1.0f;

	uint32_t shootTimerMax_ = 10;
	uint32_t shootTimerFlame_ = 0;

	float walkAnimationFlame_ = 0.0f;
	SAnimation::Animation walkAnimationData_;

	uint32_t particleMoveIndex_ = 0;
	Math::Vector::Vector3 resetPos_ = {};

	bool isUseGravityFlag_ = true;
	string warpFilePath_ = "";
};