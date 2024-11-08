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


#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/Particles/CharacterMoveParticle.h"

#include"Particle/PlayerDeadParticle.h"
#include"Hp/PlayerHp.h"

/// <summary>
/// 操作するCoreクラス
/// </summary>
class Player :public IObjectData, public ICollider
{
public:
	Player() {};
	~Player() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// ImGui更新
	/// </summary>
	void ImGuiUpdate();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();


	/// <summary>
	/// 当たった時の処理
	/// </summary>
	/// <param name="c"></param>
	void OnCollision(ICollider* c, IObjectData* objData)override;

	/// <summary>
	/// 状態遷移
	/// </summary>
	/// <param name="newState"></param>
	void ChangeState(unique_ptr<IPlayerState>newState);


	/// <summary>
	/// パーティクル表示
	/// </summary>
	void DrawParticle();

#pragma region Command

	/// <summary>
	/// JampCommand
	/// </summary>
	void Jamp();

	/// <summary>
	///　MoveCommand
	/// </summary>
	/// <param name="speed"></param>
	void Move(float speed);

	/// <summary>
	/// 射撃コマンド
	/// </summary>
	void Shoot();

	/// <summary>
	/// 位置を初期化
	/// </summary>
	void ResetPos() { gameObjectManager_->GetObj3dData(this->INameable::name_)->GetWorldTransform().transform.translate = resetPos_; }
#pragma endregion

#pragma region Get
	bool GetIsJamp() { return isJamp_; }
	bool GetIsShoot() { return isShoot_; }
	bool& GetIsGameEnd() { return isGameEnd_; }
	bool GetIsGoal() { return isGoal_; }

	bool& GetIsInvincible() { return isInvincible_; }
	string& GetWarpFilePath() { return warpFilePath_; }
	bool GetIsUseGravityFlag() { return isUseGravityFlag_; }
	bool GetIsDeadAnimationComplite() { return isDeadAnimationComplite_; }
	bool& GetIsChangeDeadAnimation() { return isChangeDeadAnimation_; }
	PlayerDeadParticle* GetDeadParticle() { return deadParticle_.get(); }

#pragma endregion

#pragma region Set
	void SetRockState(bool f) { isRockState_ = f; }

	void SetIsUseGravityFlag(bool f) { isUseGravityFlag_ = f; }
	void SetIsGameEnd(bool f) { isGameEnd_ = f; }
	void SetIsDeadComplite(bool f) { isDeadAnimationComplite_ = f; }
	void SetPlayerHP(shared_ptr<PlayerHp> hp) { hp_ = hp; }
	void SetReduceHpFunc(std::function<void()>f) { reduceHpFunc_ = f; }

#pragma endregion

private:
	function<void()>reduceHpFunc_ = nullptr;

	/// <summary>
	/// ダメージ更新
	/// </summary>
	void DamageUpdate();

	/// <summary>
	/// コントローラーのデッドゾーン
	/// </summary>
	/// <param name="v"></param>
	void ControlDeadZone(Math::Vector::Vector2& v);

	unique_ptr<IPlayerState>state_ = nullptr;


	bool isJamp_ = false;
	bool isShoot_ = false;
	bool isRockState_ = false;
	bool isInvincible_ = false;
	bool isGameEnd_ = false;
	bool isGoal_ = false;

	bool isDeadAnimationComplite_ = false;

	bool isChangeDeadAnimation_ = false;


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

	unique_ptr<PlayerDeadParticle>deadParticle_ = nullptr;

	weak_ptr<PlayerHp> hp_;
};