#pragma once
#include"Pch.h"
#include"state/IGunEnemyState.h"
#include"GameObject/ObjectInterface/ObjectComponent.h"

/// <summary>
/// 銃の敵の抽象クラス
/// </summary>
class IGunEnemy :public ObjectComponent
{
public:
	IGunEnemy() {};
	virtual ~IGunEnemy() {};

	/// <summary>
	/// state切替
	/// </summary>
	/// <param name="state"></param>
	void ChangeState(unique_ptr<IGunEnemyState>state);

#pragma region Get
	bool& GetIsEnd() { return isEnd_; }
	bool& GetIsDead() { return isDead_; }
#pragma endregion

#pragma region Set

	void SetIsShot(bool f) { isShot_ = f; }
	void SetEnemyNumber(int32_t number) { enemyNumber_ = number; }

#pragma endregion


private:

protected:

	bool IsHit_ = false;
	bool isDead_ = false;
	bool isEnd_ = false;
	bool isShot_ = false;

	int32_t enemyNumber_ = 0;
	unique_ptr<IGunEnemyState>state_ = nullptr;
};
