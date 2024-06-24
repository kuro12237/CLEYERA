#include "Block.h"

void Block::Initialize(TransformEular t)
{
	this->transform_ = t;
	name_ = "Map";
	SetObjectData(this->transform_);
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
