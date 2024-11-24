#include "GunEnemyStateMove.h"

void GunEnemyStateMove::Initialize([[maybe_unused]] GunEnemy* e)
{
}

void GunEnemyStateMove::Update(GunEnemy* e)
{
	auto& transform = GameObjectManager::GetInstance()->GetObj3dData(e->INameable::GetName())->GetWorldTransform().transform;
	transform.translate.x += e->GetSpeed();

	deltaTime_ += DeltaTimer(flame_);

	if (deltaTime_ >= deltaTimerMax_)
	{
		e->ChangeState(make_unique<GunEnemyStateShoot>());
		return;
	}

}
