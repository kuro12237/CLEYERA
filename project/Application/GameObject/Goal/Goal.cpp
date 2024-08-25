#include "Goal.h"

void Goal::Initialize()
{
	name_ = "Goal";
	gameObjIncetance_ = GameObjectManager::GetInstance();
	auto& transform = gameObjIncetance_->GetObj3dData(name_)->GetWorldTransform().transform;
	SetObjectData(transform);
	aabb_ = { { -1.0f,-1.0f,-1.0f }, { 1.0f,1.0f,1.0f } };
	id_ = kGoalId;

	GoalParticle::GetInstance()->Initialize();

	gameObjIncetance_->SetObjectPipline(make_unique<Sprite3dAddNoneWritePiplineCommand>(),backName_);
}

void Goal::Update()
{
	auto& transform = gameObjIncetance_->GetObj3dData(name_)->GetWorldTransform().transform;
	transform.rotate.z += float(numbers::pi * 0.01f);

	//particle
	Math::Vector::Vector3 emitterOffset = {0.0f,0.0f,-1.0f};
	auto& emitter = GoalParticle::GetInstance()->GetEmitters()->GetEmitParam()[0];
	emitter.translate = Math::Vector::Add(transform.translate,emitterOffset);
	//emitter.rotate = transform.rotate;
	emitter.rotate.z += float(numbers::pi * 0.01f);
	auto& field = GoalParticle::GetInstance()->GetField()[0].GetParam(0);
	field.translate = transform.translate;

	GoalParticle::GetInstance()->Update();
}

void Goal::OnCollision(ICollider* c)
{
	if (c->GetId() == kPlayerId)
	{
		isGoalFlag_ = true;
	}
}
