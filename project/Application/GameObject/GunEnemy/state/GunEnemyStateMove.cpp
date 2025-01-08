#include "GunEnemyStateMove.h"

void GunEnemyStateMove::Initialize([[maybe_unused]] IGunEnemy* e)
{
	e;
}

void GunEnemyStateMove::Update(IGunEnemy* e)
{
	auto& transform = e->GetObjectData().lock()->GetWorldTransform().transform;

	const float degree = 90.0f;

	if (e->GetVelocity().x >= 0.0f)
	{
		transform.rotate.y = Math::Vector::degreesToRadians(degree);
	}
	else
	{
		transform.rotate.y = -Math::Vector::degreesToRadians(degree);
	}

	deltaTime_ += DeltaTimer(flame_);

	if (deltaTime_ >= deltaTimerMax_)
	{
		e->ChangeState(make_unique<GunEnemyStateShoot>());
		return;
	}
}
