#include "GunEnemyStateDeadAnimation.h"

void GunEnemyStateDeadAnimation::Initialize(IGunEnemy* e)
{
	gameObjectManager_ = GameObjectManager::GetInstance();
	gameObjectManager_->SetObjectPipline(make_unique<Phong3dDissolvePipline>(), e->INameable::GetName());

	e->GetObjectData().lock()->DeleateParent();

	Math::Vector::Vector3 min = {-0.4f,0.2f,0.0f};
	Math::Vector::Vector3 max = {0.2f,0.4f,0.0f};

	for (size_t i = 0; i < impactVec_.size(); i++)
	{
		impactVec_[i] = RandomGenerator::GetParam<Math::Vector::Vector3>(min, max);
	}

	e->SetVelocity(impactVec_[0]);
}

void GunEnemyStateDeadAnimation::Update(IGunEnemy* e)
{
	auto& coreDesc = gameObjectManager_->GetObjectDesc(e->INameable::GetName());

	flame_ += flameAdd_;

	//edge設定
	coreDesc.edgeDesc.minmax = { -0.1f,0.2f };
	coreDesc.edgeDesc.mask = flame_;

	if (flame_ >= flameMax_)
	{
		bool& flag = e->GetIsDead();
		flag = true;
	}

}
