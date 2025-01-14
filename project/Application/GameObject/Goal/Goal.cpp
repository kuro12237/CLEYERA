#include "Goal.h"

void Goal::Initialize()
{
	gameObjIncetance_ = GameObjectManager::GetInstance();

	string indexCount = to_string(index_);

	string GoalCountName = "";
	if (indexCount == "0")
	{
	}
	else {
		GoalCountName = "." + string(3 - to_string(index_).length(), '0') + to_string(index_);
	}

	INameable::name_ = "Goal" + GoalCountName;

	AABB aabb = { { -1.0f,-1.0f,-1.0f }, { 1.0f,1.0f,1.0f } };

	//dataをセット
	objectData_ = gameObjectManager_->GetObj3dData(INameable::name_);

	//コライダーセット
	this->SetColliderParamData();
	collider_->SetAABB(aabb);
	collider_->SetIsExtrusion(false);
	collider_->SetMask(CollisionMask::kPortalMask);
	collider_->SetAttribute(CollisionMask::kPortalAttribute);

	gameObjIncetance_->SetObjectPipline(make_unique<Sprite3dAddNoneWritePiplineCommand>(), backName_ + GoalCountName);

	auto& emitter = GoalParticle::GetInstance()->GetEmitters()->GetEmitParam()[index_];
	auto& field = GoalParticle::GetInstance()->GetField()[0].GetParam(index_);
	//emit
	float kParticleRadious = 2.0f;
	uint32_t kSpownMax = 4;
	float kParticleFrequencyTime = 0.1f;
	float kParticleScale = 0.25f;
	float kColorDecay = 0.02f;
	Math::Vector::Vector4 kColor = ColorConverter::ColorConversion(0xffff00ff);

	auto& control = GoalParticle::GetInstance()->GetEmitters()->GetControlParam()[index_];
	control.useFlag_ = true;
	control.frequencyTime = kParticleFrequencyTime;
	emitter.count = kSpownMax;
	emitter.radious = kParticleRadious;
	emitter.scaleSizeMin = { kParticleScale, kParticleScale, kParticleScale };
	emitter.scaleSizeMax = { kParticleScale,kParticleScale,kParticleScale };
	emitter.colorDecayMax = { 0.0f,0.0f,0.0f,kColorDecay };
	emitter.colorDecayMin = { 0.0f,0.0f,0.0f,kColorDecay };
	emitter.color = kColor;

	//fieldParticle
	const float kSize = 8.0f;
	float power = 0.05f;
	field.use = 1;
	field.sizeMax = { kSize,kSize,kSize };
	field.sizeMin = { -kSize,-kSize,-kSize };
	field.suctionPower = power;
}

void Goal::Update()
{
	auto& transform = gameObjIncetance_->GetObj3dData(INameable::name_)->GetWorldTransform().transform;
	transform.rotate.z += float(numbers::pi * 0.01f);

	//particle
	Math::Vector::Vector3 emitterOffset = { 0.0f,0.0f,-1.0f };
	auto& emitter = GoalParticle::GetInstance()->GetEmitters()->GetEmitParam()[index_];
	emitter.translate = Math::Vector::Add(transform.translate, emitterOffset);
	//emitter.rotate = transform.rotate;
	emitter.rotate.z += float(numbers::pi * 0.01f);
	auto& field = GoalParticle::GetInstance()->GetField()[0].GetParam(index_);
	field.translate = transform.translate;
}

void Goal::OnCollision([[maybe_unused]] IObjectData* objData)
{
	auto c = objData->GetCollider();
	if (c->GetId() == ObjectId::kPlayerId)
	{
		isGoalFlag_ = true;
	}
}
