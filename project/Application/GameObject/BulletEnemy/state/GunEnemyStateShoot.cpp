#include "GunEnemyStateShoot.h"

void GunEnemyStateShoot::Initialize([[maybe_unused]]GunEnemy* e)
{
}

void GunEnemyStateShoot::Update(GunEnemy* e)
{

	deltaTime_ += DeltaTimer(flame_);

	if (deltaTime_ >= deltaTimerMax_)
	{
		e->CreateBullet(GameObjectManager::GetInstance()->GetObj3dData(e->INameable::GetName())->GetWorldTransform().GetWorldPosition());

		e->ChangeState(make_unique<GunEnemyStateMove>());
		return;
	}

}
