#pragma once
#include"GameObject/ObjectManager/IObjectData.h"
#include"state/IPlayerBulletState.h"
#include"state/PlayerBulletStateNone.h"

class PlayerBullet:public IObjectData
{
public:
	PlayerBullet() {};
	~PlayerBullet() {};

	void Initialize();

	void Update();

#pragma region Set

	void SetSpownPos(Math::Vector::Vector3 pos) { spownPos_ = pos; }

	void SetVelocity(Math::Vector::Vector3 v) { velocity_ = v; }

#pragma endregion

#pragma region Get

	bool GetIsDeadFlag() { return isDead_; }

#pragma endregion

private:

	unique_ptr<IPlayerBulletState>state_ = nullptr;

	Math::Vector::Vector3 spownPos_ = {};
	bool isDead_ = false;
	uint32_t timer_ = 0;
	const float speed_ = 0.75f;


};