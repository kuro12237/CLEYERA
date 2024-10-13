#include "Block.h"

void Block::Initialize(string name, uint32_t index)
{
	name_ = name + to_string(index);

	GameObjectManager* instance = GameObjectManager::GetInstance();
	auto& data = instance->GetObjInstancingData(name)->GetTransforms()[index];
	SetObjectData(data->GetTransform());
	SetAABB(data->GetAABB());

	id_ = kNormalBlock;
	attribute_ = CollisionMask::kBlockAttribute;
	mask_ = CollisionMask::kBlockMask;
}

void Block::Update()
{
	//hit•{ƒ‰ƒu‚ðƒNƒŠƒA
	ClearExtrusion();
	ClearHitDirection();
}

void Block::OnCollision(ICollider* c)
{
	c;
}
