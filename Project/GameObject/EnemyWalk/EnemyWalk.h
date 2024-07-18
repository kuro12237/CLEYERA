#pragma once
#include"STransformEular.h"
#include"Pch.h"
#include"GameObject/ObjectManager/IObjectData.h"
#include"GameObject/GameCollider/ICollider.h"
#include"Input.h"
#include"Utility/ObjectId/GameObjectId.h"

#include"state/IEnemyWalkState.h"
#include"state/EnemyWalkStateMove.h"

class EnemyWalk :public IObjectData, public ICollider
{
public:
	EnemyWalk() {};
	~EnemyWalk() {};

	void Initialize();

	void Update();

	void OnCollision(ICollider* c)override;

#pragma region Get

	bool GetIsHit() { return IsHit_; }

	bool GetIsDead() { return isDead_; }

	float GetSpeed() { return speed_; }

#pragma endregion

private:

	bool IsHit_ = false;
	bool isDead_ = false;


	float speed_ = -0.1f;

	unique_ptr<IEnemyWalkState>state_ = nullptr;

};

