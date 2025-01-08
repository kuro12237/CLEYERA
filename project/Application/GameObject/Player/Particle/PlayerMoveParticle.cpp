#include "PlayerMoveParticle.h"

void PlayerMoveParticle::Initialize()
{
	name_ = "PlayerMoveParticle";
	this->Create();

	texHandle_ = Engine::Manager::TextureManager::LoadDDSTexture("GameObject/cloud/cloud.dds");
	particle_->SetTexhandle(texHandle_);

	auto& emitter = boxEmitter_->GetControlParam()[0];

	emitter.useFlag_ = true;
	emitter.frequencyTime = 0.04f;

	auto& param = boxEmitter_->GetEmitParam()[0];

	param.sizeMax = { 0.01f,0.01f, 0.01f };
	param.sizeMin = { -0.01f,-0.01f, -0.01f };

	param.velocityMax.y = 0.01f;
	param.velocityMin.y = 0.01f;

	param.scaleSizeMin = { 0.1f,0.1f,0.1f };
	param.scaleSizeMax = { 0.1f,0.1f,0.1f };
	param.scaleVelocityMax = { 0.025f,0.025f,0.025f };
	param.scaleVelocityMin = { 0.025f,0.025f,0.025f };
	param.colorDecayMin.w = 0.035f;
	param.colorDecayMax.w = 0.035f;

}

void PlayerMoveParticle::Update()
{
	auto &param = boxEmitter_->GetEmitParam()[0];
	if (isEmit_)
	{
		param.translate = *playerWorldPos_;
		AABB aabb_ = GameObjectManager::GetInstance()->GetObj3dData("Player")->GetAABB();
		Math::Vector::Vector3 particleOffset = { 0.0f, aabb_.min.y / 2.0f + aabb_.min.y / 4.0f,-2.0f };
		param.translate.y += particleOffset.y;
		param.translate.z += particleOffset.z;
		param.count = 1;
	}
	else
	{
		param.count = 0;
	}

	boxEmitter_->Emit(particle_);
	boxEmitter_->Update();
	particle_->CallBarrier();
	particle_->Update();
}
