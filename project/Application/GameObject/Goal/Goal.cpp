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
	float kParticleRadious = 4.0f;
	uint32_t kSpownMax = 12;
	float kParticleFrequencyTime = 1.0f;
	float kParticleScale = 0.5f;

	auto &emitter = GoalParticle::GetInstance()->GetEmitters()->GetEmitParam()[0];
	auto& control = GoalParticle::GetInstance()->GetEmitters()->GetControlParam()[0];
	control.useFlag_ = true;
	control.frequencyTime = kParticleFrequencyTime;

	emitter.count = kSpownMax;
	emitter.translate = transform.translate;
	emitter.radious = kParticleRadious;
	emitter.scaleSizeMin = { kParticleScale, kParticleScale, kParticleScale };
	emitter.scaleSizeMax = {kParticleScale,kParticleScale,kParticleScale};
}

void Goal::Update()
{
	auto& transform = gameObjIncetance_->GetObj3dData(name_)->GetWorldTransform().transform;
	transform.rotate.z += float(numbers::pi * 0.01f);
	auto& emitter = GoalParticle::GetInstance()->GetEmitters()->GetEmitParam()[0];
	emitter.translate = transform.translate;
	emitter.rotate = transform.rotate;

	GoalParticle::GetInstance()->Update();
}

void Goal::OnCollision(ICollider* c)
{
	if (c->GetId() == kPlayerId)
	{
		isGoalFlag_ = true;
	}
}
