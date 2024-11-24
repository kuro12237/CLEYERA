#include "GunEnemyStateMove.h"

void GunEnemyStateMove::Initialize([[maybe_unused]] GunEnemy* e)
{
}

void GunEnemyStateMove::Update(GunEnemy* e)
{
	auto& transform = GameObjectManager::GetInstance()->GetObj3dData(e->INameable::GetName())->GetWorldTransform().transform;
	transform.translate.x += e->GetSpeed();
	
	if (e->GetSpeed() >= 0.0f)
	{
		transform.rotate.y = Math::Vector::degreesToRadians(90.0f);
	}
	else
	{

		transform.rotate.y = Math::Vector::degreesToRadians(-90.0f);
	}


	deltaTime_ += DeltaTimer(flame_);

	if (deltaTime_ >= deltaTimerMax_)
	{
		e->ChangeState(make_unique<GunEnemyStateShoot>());
		return;
	}

}
