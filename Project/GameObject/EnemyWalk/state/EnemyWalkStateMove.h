#pragma once
#include"IEnemyWalkState.h"
#include"../EnemyWalk.h"

class EnemyWalkStateMove:public IEnemyWalkState
{
public:
	EnemyWalkStateMove() {};
	~EnemyWalkStateMove() {};

	void Initialize()override;

	void Update(EnemyWalk* e)override;

private:

	float speed_ = -0.01f;

};


