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
#include"state/PlayerStateDeadAnimation.h"
#include"state/PlayerStateInvincible.h"
#include"state/PlayerStateWalk.h"
#include"state/PlayerStateJamp.h"
#include"state/PlayerStateFall.h"

#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/Particles/CharacterMoveParticle.h"

#include"Particle/PlayerDeadParticle.h"
#include"Hp/PlayerHp.h"

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
	/// �p�[�e�B�N���\��
	/// </summary>
	void DrawParticle();

	/// <summary>
	/// �����������̏���
	/// </summary>
	/// <param name="c"></param>
	void OnCollision(ICollider* c, IObjectData* objData)override;

	/// <summary>
	/// ��Ԃ�ǉ�
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template <typename T>
	void AddState() {
		std::type_index typeIdx(typeid(T));
		if (states_.find(typeIdx) == states_.end()) {
			states_[typeIdx] = std::make_unique<T>();
			states_[typeIdx]->Initialize(this);
		}
	}

	/// <summary>
	/// ��Ԃ��폜
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template <typename T>
	void MarkStateForRemoval() {
		std::type_index typeIdx(typeid(T));
		statesToRemoveQueue_.push(typeIdx);
	}

	template <typename T>
	bool IsInState() const {
		std::type_index typeIdx(typeid(T));
		return states_.find(typeIdx) != states_.end();
	}

#pragma region Command

	/// <summary>
	/// JampCommand
	/// </summary>
	void Jamp();

	/// <summary>
	///�@MoveCommand
	/// </summary>
	/// <param name="speed"></param>
	void Move();

	/// <summary>
	/// �ˌ��R�}���h
	/// </summary>
	void Shoot();

	/// <summary>
	/// �ʒu��������
	/// </summary>
	void ResetPos() { gameObjectManager_->GetObj3dData(this->INameable::name_)->GetWorldTransform().transform.translate = resetPos_; }
#pragma endregion

	void WalkanimationAddFlame(const float& flame) { walkAnimationFlame_ += flame; }

#pragma region Get
	bool GetIsShoot() { return isShoot_; }
	bool& GetIsGameEnd() { return isGameEnd_; }
	string& GetWarpFilePath() { return warpFilePath_; }
	bool GetIsUseGravityFlag() { return isUseGravityFlag_; }
	bool GetIsDeadAnimationComplite() { return isDeadAnimationComplite_; }
	bool& GetIsChangeDeadAnimation() { return isChangeDeadAnimation_; }
	PlayerDeadParticle* GetDeadParticle() { return deadParticle_.get(); }

	float GetWalkAnimationFlame()const  { return walkAnimationFlame_; }
#pragma endregion

#pragma region Set
	void SetIsUseGravityFlag(bool f) { isUseGravityFlag_ = f; }
	void SetIsGameEnd(bool f) { isGameEnd_ = f; }
	void SetIsDeadComplite(bool f) { isDeadAnimationComplite_ = f; }
	void SetPlayerHP(shared_ptr<PlayerHp> hp) { hp_ = hp; }

	void SetReduceHpFunc(std::function<void()>f) { reduceHpFunc_ = f; }
	void SetDamageUpdateFunc(std::function<void()>f) { damegeUpdateFunc_ = f; }
	void SetDamageUpdateEndFunc(std::function<void()>f) { damegeUpdateEndFunc_ = f; }
#pragma endregion

private:
	function<void()>reduceHpFunc_ = nullptr;
	function<void()>damegeUpdateFunc_ = nullptr;
	function<void()>damegeUpdateEndFunc_ = nullptr;



	std::unordered_map<std::type_index, std::unique_ptr<IPlayerState>> states_;
	std::queue<std::type_index> statesToRemoveQueue_;


	bool isShoot_ = false;
	bool isGameEnd_ = false;

	bool isDeadAnimationComplite_ = false;

	bool isChangeDeadAnimation_ = false;


	float damegeFlame_ = 0.0f;
	uint32_t damegeCoolTimer_ = 0;
	uint32_t damageCoolTimerMax_ = 2;

	float vinatteFactor_ = 1.0f;

	uint32_t shootTimerMax_ = 10;
	uint32_t shootTimerFlame_ = 0;

	SAnimation::Animation animationData_;

	float walkAnimationFlame_ = 0.0f;
	SAnimation::Animation walkAnimationData_;

	float jampAnimationFlame_ = 0.0f;
	SAnimation::Animation jampAnimationData_;

	float resultDataFlame_ = 0.0f;

	uint32_t particleMoveIndex_ = 0;
	Math::Vector::Vector3 resetPos_ = {};

	bool isUseGravityFlag_ = true;
	string warpFilePath_ = "";

	unique_ptr<PlayerDeadParticle>deadParticle_ = nullptr;

	weak_ptr<PlayerHp> hp_;

	string walkAnimationFilePath = "";
};