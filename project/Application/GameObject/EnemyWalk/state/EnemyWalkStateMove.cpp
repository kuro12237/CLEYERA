#include "EnemyWalkStateMove.h"

void EnemyWalkStateMove::Initialize([[maybe_unused]] EnemyWalk* e)
{
}

void EnemyWalkStateMove::Update([[maybe_unused]] EnemyWalk* e)
{
	auto& transform = GameObjectManager::GetInstance()->GetObj3dData(e->INameable::GetName())->GetWorldTransform().transform;
	
	//大きさをもとに回転させる
	transform.rotate.z -= e->GetVelocity().x * 1.0f / e->GetObjectData().lock()->GetWorldTransform().GetWorldScale().x;
}
