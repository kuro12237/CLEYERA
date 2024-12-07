#include "GunEnemyStateShoot.h"

void GunEnemyStateShoot::Initialize([[maybe_unused]]IGunEnemy* e)
{
}

void GunEnemyStateShoot::Update(IGunEnemy* e)
{
	deltaTime_ += DeltaTimer(flame_);

	if (deltaTime_ >= deltaTimerMax_)
	{
		e->SetIsShot(true);
		e->ChangeState(make_unique<GunEnemyStateMove>());
		return;
	}
}
