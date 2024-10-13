#include "BlockManager.h"

void BlockManager::Initialize()
{
	auto& transforms = GameObjectManager::GetInstance()->GetObjInstancingData(name_)->GetTransforms();

	for (int i = 0; i < int(transforms.size()); i++)
	{
		shared_ptr<Block>block = make_shared<Block>();
		block->Initialize(name_, i);
		blocks_.push_back(block);
	}
}

void BlockManager::Update()
{
	for (shared_ptr<Block>& b : blocks_)
	{
		b->Update();
	}
}
