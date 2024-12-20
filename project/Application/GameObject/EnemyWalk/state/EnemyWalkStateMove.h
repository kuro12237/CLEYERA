#pragma once
#include"IEnemyWalkState.h"
#include"../EnemyWalk.h"

/// <summary>
/// 歩く敵の状態::移動中
/// </summary>
class EnemyWalkStateMove:public IEnemyWalkState
{
public:
	EnemyWalkStateMove() {};
	~EnemyWalkStateMove() {};

	void Initialize([[maybe_unused]] EnemyWalk* e)override;

	void Update([[maybe_unused]] EnemyWalk* e)override;
private:
};


