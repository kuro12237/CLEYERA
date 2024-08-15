#include "EnemyWalkStateDead.h"

void EnemyWalkStateDead::Initialize()
{
	gameObjIncetance_ = GameObjectManager::GetInstance();
}

void EnemyWalkStateDead::Update([[maybe_unused]] EnemyWalk* e)
{
	auto& desc = gameObjIncetance_->GetObjectDesc(e->GetName());
	desc.edgeDesc.minmax = { -0.1f,0.2f };
	desc.edgeDesc.mask += 1.0f / 60.0f;
	desc.edgeDesc.edgeColor = { 0.0f,1.0f,0.0f,0.0f };
	flame_ += 1.0f / 60.0f;
	if (flame_ >= flameMax_)
	{
		bool& flag = e->GetIsEnd();
		flag = true;
	}
}
