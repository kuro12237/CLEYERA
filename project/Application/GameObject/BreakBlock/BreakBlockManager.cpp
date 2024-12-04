#include "BreakBlockManager.h"

void BreakBlockManager::Initialize()
{
	auto& transforms = GameObjectManager::GetInstance()->GetObjInstancingData(name_)->GetTransforms();

	for (int i = 0; i < int(transforms.size()); i++)
	{
		shared_ptr<BreakBlock>block = make_shared<BreakBlock>();
		block->Initialize(name_, i);
		blocks_.push_back(move(block));
	}

	gameObjectManager_ = GameObjectManager::GetInstance();
}

void BreakBlockManager::Update()
{
	for (shared_ptr<BreakBlock>& b : blocks_)
	{
		weak_ptr<BreakBlock>it = b;
		auto obj = it.lock();
		obj->Update();


		if (obj->GetIsDead())
		{
			gameObjectManager_->GetObjInstancingData(name_)->GetTransforms()[obj->GetInstancingIndex()]->SetBreakFlag(true);
		}
	}
}
