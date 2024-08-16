#include "EnemyWalkStateMove.h"

void EnemyWalkStateMove::Initialize([[maybe_unused]] EnemyWalk* e)
{
}

void EnemyWalkStateMove::Update([[maybe_unused]] EnemyWalk* e)
{
	auto& transform = GameObjectManager::GetInstance()->GetObj3dData(e->GetName())->GetWorldTransform().transform;
	transform.translate.x += e->GetSpeed();
	transform.rotate.z -= e->GetSpeed();
}
