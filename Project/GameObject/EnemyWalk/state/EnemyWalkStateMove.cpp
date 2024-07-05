#include "EnemyWalkStateMove.h"

void EnemyWalkStateMove::Initialize()
{
}

void EnemyWalkStateMove::Update(EnemyWalk* e)
{
	TransformEular transform = e->GetTransform();
	transform.translate.x += speed_;
	e->SetTransform(transform);
}
