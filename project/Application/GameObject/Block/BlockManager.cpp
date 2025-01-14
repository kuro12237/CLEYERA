#include "BlockManager.h"

using namespace Engine::Particle;
void BlockManager::Initialize()
{
	auto& transforms = GameObjectManager::GetInstance()->GetObjInstancingData(name_)->GetTransforms();


	boxField_ = make_unique<ParticleField<FieldType::FieldHitBox>>();
	boxField_->CreateType(name_ + "Particle");
	for (int i = 0; i < int(transforms.size()); i++)
	{
		shared_ptr<Block>block = make_shared<Block>();

		block->SetName(name_);
		block->SetBlockIndex(i);
		block->SetParticleField(boxField_.get());
		block->Initialize();
		blocks_.push_back(block);
	}
}

void BlockManager::Update()
{
	for (shared_ptr<Block>& b : blocks_)
	{
		b->Update();
	}

	boxField_->Update();
}
