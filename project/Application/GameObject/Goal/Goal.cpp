#include "Goal.h"

void Goal::Initialize()
{
	name_ = "Goal";
	gameObjIncetance_ = GameObjectManager::GetInstance();
	auto& transform = gameObjIncetance_->GetObj3dData(name_)->GetWorldTransform().transform;
	SetObjectData(transform);
	aabb_ = { { -1.0f,-1.0f,-1.0f }, { 1.0f,1.0f,1.0f } };
	id_ = kGoalId;
}

void Goal::Update()
{
	auto& transform = gameObjIncetance_->GetObj3dData(name_)->GetWorldTransform().transform;

	transform.rotate.z += float(numbers::pi * 0.1);
}

void Goal::OnCollision(ICollider* c)
{
	if (c->GetId() == kPlayerId)
	{
		isGoalFlag_ = true;
	}
}
