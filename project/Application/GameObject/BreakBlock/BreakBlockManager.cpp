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
}

void BreakBlockManager::Update()
{
	for (shared_ptr<BreakBlock>& b : blocks_)
	{
		weak_ptr<BreakBlock>it = b;
		it.lock()->Update();
	}
}
