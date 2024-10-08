#include "Block.h"

void Block::Initialize(string name, uint32_t index)
{
	name_ = name + to_string(index);

	GameObjectManager* instance = GameObjectManager::GetInstance();
	auto& data = instance->GetObjInstancingData(name)->GetTransforms()[index];
	SetObjectData(data->GetTransform());
	SetAABB(data->GetAABB());

	SetUvScale({ 0.0f,0.0f,10.0f });
	id_ = kNormalBlock;
	attribute_ = CollisionMask::kBlockAttribute;
	mask_ = CollisionMask::kBlockMask;
}

void Block::Update()
{
	//hit府ラブをクリア
	ClearExtrusion();
	ClearHitDirection();
}

void Block::OnCollision(ICollider* c)
{
	c;
}
