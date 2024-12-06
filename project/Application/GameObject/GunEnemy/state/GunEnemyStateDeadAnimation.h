#pragma once
#include"IGunEnemyState.h"
#include"../GunEnemy.h"

#include"GunEnemyStateShoot.h"

/// <summary>
/// 死ぬ状態
/// </summary>
class GunEnemyStateDeadAnimation :public IGunEnemyState
{
public:
	GunEnemyStateDeadAnimation() {};
	~GunEnemyStateDeadAnimation() {};

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="本体"></param>
	void Initialize(GunEnemy* e);


	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="本体"></param>
	void Update(GunEnemy* e);
private:

	GameObjectManager* gameObjectInstance_ = nullptr;
	float flame_ = 0.0f;
	float flameMax_ = 1.0f;
	float flameAdd_ = 1.0f / 120.0f;
	int32_t deltaTime_ = 0;
	int32_t deltaTimerMax_ = 3;
};
