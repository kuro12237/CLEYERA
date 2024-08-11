#pragma once
#include"IEnemyWalkState.h"
#include"../EnemyWalk.h"

class EnemyWalkStateDead :public IEnemyWalkState
{
public:
	EnemyWalkStateDead() {};
	~EnemyWalkStateDead() {};

	void Initialize()override;

	void Update([[maybe_unused]] EnemyWalk* e)override;

private:

	float flame_ = 0.0f;
	float flameMax_ = 60.0f;
};
