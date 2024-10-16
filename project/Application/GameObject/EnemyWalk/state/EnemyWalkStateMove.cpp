#include "EnemyWalkStateMove.h"

void EnemyWalkStateMove::Initialize([[maybe_unused]] EnemyWalk* e)
{
}

void EnemyWalkStateMove::Update([[maybe_unused]] EnemyWalk* e)
{
	auto& transform = GameObjectManager::GetInstance()->GetObj3dData(e->GetName())->GetWorldTransform().transform;
	transform.translate.x += e->GetSpeed();
	//大きさをもとに回転させる
	transform.rotate.z -= e->GetSpeed() * 1.0f / e->GetpTransform().scale.x;
}
