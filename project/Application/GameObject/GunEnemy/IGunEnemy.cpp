#include "IGunEnemy.h"

void IGunEnemy::ChangeState(unique_ptr<IGunEnemyState> state)
{
	state_ = move(state);
	state_->Initialize(this);
}

