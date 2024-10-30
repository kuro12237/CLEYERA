#pragma once
#include"STransformEular.h"
#include"Pch.h"
#include"GameObject/ObjectInterface/IObjectData.h"

#include"GameObject/GameCollider/ICollider.h"
#include"Input.h"
#include"Utility/ObjectId/GameObjectId.h"

#include"state/IEnemyWalkState.h"
#include"state/EnemyWalkStateMove.h"
#include"state/EnemyWalkStateDead.h"

/// <summary>
/// •à‚­“G
/// </summary>
class EnemyWalk :public IObjectData, public ICollider
{
public:
	EnemyWalk() {};
	~EnemyWalk() {};

	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize();

	/// <summary>
	/// XV
	/// </summary>
	void Update();

	/// <summary>
	/// “–‚½‚Á‚½
	/// </summary>
	void OnCollision(ICollider* c, IObjectData* objData)override;

	/// <summary>
	/// ó‘Ô‘JˆÚ
	/// </summary>
	/// <param name="state"></param>
	void ChangeState(unique_ptr<IEnemyWalkState>state);

#pragma region Get
	bool &GetIsHit() { return IsHit_; }
	bool &GetIsDead() { return isDead_; }
	bool &GetIsEnd() { return isEnd_; }
	float &GetSpeed() { return speed_; }
#pragma endregion

private:

	bool IsHit_ = false;
	bool isDead_ = false;
	bool isEnd_ = false;

	float speed_ = -0.1f;

	unique_ptr<IEnemyWalkState>state_ = nullptr;
	GameObjectManager* gameObjIncetance_ = nullptr;
};

