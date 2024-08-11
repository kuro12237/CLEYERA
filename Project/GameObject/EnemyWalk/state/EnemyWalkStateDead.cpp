#include "EnemyWalkStateDead.h"

void EnemyWalkStateDead::Initialize()
{
}

void EnemyWalkStateDead::Update([[maybe_unused]] EnemyWalk* e)
{
	flame_ ++;
	if (flame_ >= flameMax_)
	{
		bool& flag = e->GetIsEnd();
		flag = true;
	}
}
