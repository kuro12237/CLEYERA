#pragma once
#include"GameObject/ObjectManager/IObjectData.h"
#include"GameObject/GameCollider/ICollider.h"

#include"state/IPlayerBulletState.h"
#include"state/PlayerBulletStateNone.h"

#include"Utility/ObjectId/GameObjectId.h"

class PlayerBullet:public IObjectData,public ICollider
{
public:
	PlayerBullet() {};
	~PlayerBullet() {};

	void Initialize();

	void Update();

	void OnCollision(ICollider* c)override;

#pragma region Set

	void SetSpownPos(Math::Vector::Vector3 pos) { spownPos_ = pos; }

	void SetVelocity(Math::Vector::Vector3 v) { velocity_ = v; }

	void SetPlayerSpeed(Math::Vector::Vector3 v) { playerSpeed_ = v; }
#pragma endregion

#pragma region Get

	bool GetIsDeadFlag() { return isDead_; }

#pragma endregion

private:

	unique_ptr<IPlayerBulletState>state_ = nullptr;

	Math::Vector::Vector3 playerSpeed_ = {};
	Math::Vector::Vector3 spownPos_ = {};
	bool isDead_ = false;
	uint32_t timer_ = 0;
	const float speed_ = 0.5f;

};