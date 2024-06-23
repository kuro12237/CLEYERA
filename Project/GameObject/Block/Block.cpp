#include "Block.h"

void Block::Initialize(TransformEular t)
{
	this->transform_ = t;
	name_ = "Map";
	SetObjectData(this->transform_);
}

void Block::Update()
{
}

void Block::OnCollision(ICollider* c)
{
	c;
}
