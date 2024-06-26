#include "BlockManager.h"

void BlockManager::CopyData(GameObjectManager* data)
{
	transforms_ = move(data->GetObjInstancingData(name_).transform_);
}

void BlockManager::Initialize()
{
	for (int i = 0; i < int(transforms_.size()); i++)
	{
		shared_ptr<Block>block = make_shared<Block>();
		block->Initialize(transforms_[i]->GetTransform());
		blocks_.push_back(block);
	}
}

void BlockManager::Update()
{
	uint32_t size = uint32_t(blocks_.size());
	for (int i = 0; i < int(size); i++)
	{
		transforms_[i]->SetTransformEular(blocks_[i]->GetTransform());
	}

}
