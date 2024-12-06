#include "GunEnemyStateDeadAnimation.h"

void GunEnemyStateDeadAnimation::Initialize(GunEnemy* e)
{
	e;
	gameObjectInstance_ = GameObjectManager::GetInstance();
}

void GunEnemyStateDeadAnimation::Update(GunEnemy* e)
{
	//auto& objData = gameObjectInstance_->GetObj3dDatas()[e->INameable::GetName()];
	auto& desc = gameObjectInstance_->GetObjectDesc(e->INameable::GetName());

	flame_ += flameAdd_;
	//edge設定
	desc.edgeDesc.minmax = { -0.1f,0.2f };
	desc.edgeDesc.mask = flame_;

	if (flame_ >= flameMax_)
	{
		bool& flag = e->GetIsDead();
		flag = true;
	}
}
