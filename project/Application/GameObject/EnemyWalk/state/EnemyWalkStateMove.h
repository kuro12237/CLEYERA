#pragma once
#include"IEnemyWalkState.h"
#include"../EnemyWalk.h"

/// <summary>
/// •à‚­“G‚Ìó‘Ô::ˆÚ“®’†
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


