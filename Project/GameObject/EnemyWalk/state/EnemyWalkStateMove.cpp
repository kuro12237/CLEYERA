#include "EnemyWalkStateMove.h"

void EnemyWalkStateMove::Initialize()
{
}

void EnemyWalkStateMove::Update(EnemyWalk* e)
{

	auto& transform = GameObjectManager::GetInstance()->GetObj3dData(e->GetName())->GetWorldTransform().transform;
	transform.translate.x += e->GetSpeed();
}
