#pragma once
#include"STransformEular.h"
#include"Pch.h"
#include"Input.h"
#include"PostEffect/PostEffect.h"

#include"Utility/DeltaTimer/DeltaTimer.h"
#include"Utility/ObjectId/GameObjectId.h"
#include"GameObject/ObjectManager/IObjectData.h"
#include"GameObject/GameCollider/ICollider.h"

#include"command/PlayerCommandHandler.h"

#include"state/IPlayerState.h"
#include"state/PlayerStateNone.h"
#include"state/PlayerStateRock.h"
#include"state/PlayerStateGoalAnimation.h"

#include"GameObject/ObjectManager/GameObjectManager.h"

#include"GameObject/Particles/CharacterMoveParticle.h"

class Player :public IObjectData, public ICollider
{
public:
	Player() {};
	~Player() {};

	void Initialize();

	void ImGuiUpdate();

	void Update();

	void HpUpdate();

	void OnCollision(ICollider* c)override;

	void ChangeState(unique_ptr<IPlayerState>newState);

#pragma region Command

	void Jamp();

	void Move(float speed);

	void Shoot();

#pragma endregion

#pragma region Get

	bool GetIsJamp() { return isJamp_; }

	bool GetIsShoot() { return isShoot_; }

	bool& GetIsGameEnd() { return isGameEnd_; }

	bool GetIsGoal() { return isGoal_; }

	bool& isDamageFlag() { return isDamage_; }
	bool& isInvincible() { return isInvincible_; }
	void ResetPos() {
		gameObjectInstance_->GetObj3dData(name_)->GetWorldTransform().transform.translate = resetPos_;
	}
#pragma endregion

#pragma region Set

	void SetRockState(bool f) { isRockState_ = f; }

	void SetDamageFlag(bool f) { isDamage_ = f; }

#pragma endregion

private:

	void DamageUpdate();

	void ShootCoolTimer();

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
};