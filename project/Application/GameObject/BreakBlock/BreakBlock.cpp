#include "BreakBlock.h"

void BreakBlock::Initialize(string name, uint32_t index)
{
	INameable::name_ = name + to_string(index);
	auto& transforms = gameObjectManager_->GetObjInstancingData(name)->GetTransforms()[index];
	SetObjectData(transforms->GetTransform());
	SetAABB(transforms->GetAABB());

	id_ = kNormalBlock;
	attribute_ = CollisionMask::kBlockAttribute;
	mask_ = CollisionMask::kBlockMask;
}

void BreakBlock::Update()
{
	//hitフラグをクリア
	ClearExtrusion();
	ClearHitDirection();
}

void BreakBlock::OnCollision([[maybe_unused]] ICollider* c, [[maybe_unused]] IObjectData* objData)
{
}
