#pragma once
#include"IGunEnemyState.h"
#include"../GunEnemy.h"

#include"GunEnemyStateShoot.h"

class GunEnemyStateMove:public IGunEnemyState
{
public:
	GunEnemyStateMove() {};
	~GunEnemyStateMove() {};

	 /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="本体"></param>
	void Initialize(IGunEnemy* e) ;


	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="本体"></param>
	void Update(IGunEnemy* e);
private:

	float flame_ = 0.0f;
	float flameMax_ = 1.0f;

	int32_t deltaTime_ = 0;
	int32_t deltaTimerMax_ = 3;
};
