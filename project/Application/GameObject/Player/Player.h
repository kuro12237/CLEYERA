#pragma once
#include"STransformEular.h"
#include"Pch.h"
#include"Input.h"
#include"PostEffect/PostEffect.h"

#include"Utility/DeltaTimer/DeltaTimer.h"

#include"Utility/ObjectId/GameObjectId.h"
#include"GameObject/ObjectInterface/ObjectComponent.h"

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
#include"state/PlayerStateDash.h"
#include"state/PlayerStateAim.h"

#include"Utility/ObjectManager/GameObjectManager.h"

#include"Particle/PlayerDeadParticle.h"
#include"Hp/PlayerHp.h"

/// <summary>
/// 操作するCoreクラス
/// </summary>
class Player :public ObjectComponent
{
public:
	Player() {};
	~Player() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// ImGui更新
	/// </summary>
	void ImGuiUpdate();

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;


	/// <summary>
	/// 当たった時の処理
	/// </summary>
	/// <param name="c"></param>
	void OnCollision(ObjectComponent* objData)override;

	/// <summary>
	/// 状態を追加
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
	/// 状態を削除
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

	/// <summary>
	/// stateをチェックするよう関数
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template <typename T>
	void CheckStatePush(){
		std::type_index typeIdx(typeid(T));
		statesToReturnCheckQueue_.push(typeIdx);
	}

	/// <summary>
	/// プッシュした要素がstate二あった際true
	/// </summary>
	/// <returns></returns>
	bool IsCheckStateRetuen(){
		bool result = false;

		while (!statesToReturnCheckQueue_.empty()) {
			if (states_.find(statesToReturnCheckQueue_.front()) != states_.end()) {
				result = true;
				statesToReturnCheckQueue_.pop();
				continue;
			}
			statesToReturnCheckQueue_.pop();
		}

		return result;
	}

	/// <summary>
	/// 回転を更新
	/// </summary>
	void RotateUpdate();


#pragma region Command

	/// <summary>
	/// JampCommand
	/// </summary>
	void Jamp();

	/// <summary>
	///　MoveCommand
	/// </summary>
	/// <param name="speed"></param>
	void Move();

	/// <summary>
	/// 射撃コマンド
	/// </summary>
	void Shoot();

	/// <summary>
	/// 走るコマンド
	/// </summary>
	void Dash();

	/// <summary>
	/// 照準コマンド
	/// </summary>
	void Aim();

	/// <summary>
	/// 位置を初期化
	/// </summary>
	void ResetPos() { gameObjectManager_->GetObj3dData(this->INameable::name_)->GetWorldTransform().transform.translate = resetPos_; }
#pragma endregion

	
#pragma region Get
	bool GetIsShoot() { return isShoot_; }
	bool &GetIsAim() { return isAim_; }

	bool& GetIsGameEnd() { return isGameEnd_; }
	string& GetWarpFilePath() { return warpFilePath_; }
	bool GetIsDeadAnimationComplite() { return isDeadAnimationComplite_; }
	string GetHitGoalName() { return hitGoalName_; }

#pragma endregion

#pragma region Set
	void SetIsUseGravityFlag(bool f) { isUseGravityFlag_ = f; }
	void SetIsGameEnd(bool f) { isGameEnd_ = f; }
	void SetIsDeadComplite(bool f) { isDeadAnimationComplite_ = f; }
	void SetPlayerHP(const shared_ptr<PlayerHp> &hp) { hp_ = hp; }

	void SetReduceHpFunc(const std::function<void()>&f) { reduceHpFunc_ = f; }
	void SetDamageUpdateFunc(const std::function<void()>&f) { damegeUpdateFunc_ = f; }
	void SetDamageUpdateEndFunc(const std::function<void()>&f) { damegeUpdateEndFunc_ = f; }
#pragma endregion

private:
	function<void()>reduceHpFunc_ = nullptr;
	function<void()>damegeUpdateFunc_ = nullptr;
	function<void()>damegeUpdateEndFunc_ = nullptr;

	/// <summary>
	/// SRTの更新
	/// </summary>
	void TransformUpdate();

	std::unordered_map<std::type_index, std::unique_ptr<IPlayerState>> states_;
	std::queue<std::type_index> statesToRemoveQueue_;
	std::queue<std::type_index> statesToReturnCheckQueue_;


	bool isAim_ = false;
	bool isShoot_ = false;

	bool isGameEnd_ = false;

	bool isDeadAnimationComplite_ = false;

	float damegeFlame_ = 0.0f;
	uint32_t damegeCoolTimer_ = 0;
	uint32_t damageCoolTimerMax_ = 2;


	uint32_t shootTimerMax_ = 10;
	uint32_t shootTimerFlame_ = 0;


	uint32_t particleMoveIndex_ = 0;
	Math::Vector::Vector3 resetPos_ = {};

	string warpFilePath_ = "";

	weak_ptr<PlayerHp> hp_;
	string hitGoalName_ = "";
};