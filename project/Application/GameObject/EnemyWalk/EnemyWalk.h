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
/// 歩く敵
/// </summary>
class EnemyWalk :public IObjectData, public ICollider
{
public:
	EnemyWalk() {};
	~EnemyWalk() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 当たった時
	/// </summary>
	void OnCollision(ICollider* c, IObjectData* objData)override;

	/// <summary>
	/// 状態遷移
	/// </summary>
	/// <param name="state"></param>
	void ChangeState(unique_ptr<IEnemyWalkState>state);

#pragma region Get
	bool &GetIsHit() { return isHit_; }
	bool &GetIsDead() { return isDead_; }
	bool &GetIsEnd() { return isEnd_; }
	Math::Vector::Vector3 GetImpactDirection() { return impactDirection_; }

#pragma endregion

private:

	bool isHit_ = false;
	bool isDead_ = false;
	bool isEnd_ = false;


	unique_ptr<IEnemyWalkState>state_ = nullptr;
	GameObjectManager* gameObjIncetance_ = nullptr;

	Math::Vector::Vector3 impactDirection_ = {};

};

