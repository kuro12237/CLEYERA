#include "EnemyWalkStateMove.h"

void EnemyWalkStateMove::Initialize([[maybe_unused]] EnemyWalk* e)
{
}

void EnemyWalkStateMove::Update([[maybe_unused]] EnemyWalk* e)
{
	auto& transform = GameObjectManager::GetInstance()->GetObj3dData(e->INameable::GetName())->GetWorldTransform().transform;
	transform.translate.x += e->GetSpeed();
	//‘å‚«‚³‚ð‚à‚Æ‚É‰ñ“]‚³‚¹‚é
	transform.rotate.z -= e->GetSpeed() * 1.0f / e->GetpTransform().scale.x;
}
