#pragma once
#include"IEnemyWalkState.h"
#include"../EnemyWalk.h"

class EnemyWalkStateMove:public IEnemyWalkState
{
public:
	EnemyWalkStateMove() {};
	~EnemyWalkStateMove() {};

	void Initialize()override;

	void Update([[maybe_unused]] EnemyWalk* e)override;

private:


};


