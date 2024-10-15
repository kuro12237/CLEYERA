#include "Block.h"

void Block::Initialize(string name, uint32_t index)
{
	name_ = name + to_string(index);
	auto& transforms = gameObjectManager_->GetObjInstancingData(name)->GetTransforms()[index];
	SetObjectData(transforms->GetTransform());
	SetAABB(transforms->GetAABB());

	id_ = kNormalBlock;
	attribute_ = CollisionMask::kBlockAttribute;
	mask_ = CollisionMask::kBlockMask;
}

void Block::Update()
{
	//hitフラグをクリア
	ClearExtrusion();
	ClearHitDirection();
}

void Block::OnCollision([[maybe_unused]]ICollider* c)
{
	c;
}
