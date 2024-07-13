#include "Block.h"

void Block::Initialize(TransformEular t, AABB aabb)
{

	this->transform_ = t;
	name_ = "Map";
	SetObjectData(this->transform_);
	SetAABB(aabb);
	SetUvScale({0.0f,0.0f,10.0f});
	id_ = kNormalBlock;
}

void Block::Update()
{
	this->ClearExtrusion();
	this->ClearHitDirection();
}

void Block::OnCollision(ICollider* c)
{
	c;
}
