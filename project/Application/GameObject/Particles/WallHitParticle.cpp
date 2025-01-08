#include "WallHitParticle.h"

void WallHitParticle::Initialize()
{
	this->name_ = "WallHitParticle";

	uint32_t modelHandle = Engine::Manager::ModelManager::LoadObjectFile("DfCube");
	this->Create(modelHandle);

	auto& control = boxEmitter_->GetControlParam()[0];
	control.useFlag_ = true;

	auto& emit = boxEmitter_->GetEmitParam()[0];
	emit.count = 0;

	emit.sizeMax = { 0.1f,0.1f,0.1f };
	emit.sizeMin = { -0.1f,-0.1f,-0.1f };
	emit.velocityMax = Math::Vector::Vector3(0.0f, 0.01f, 0.0f);
	emit.velocityMin = Math::Vector::Vector3(0.0f, 0.1f, 0.0f);
	emit.colorDecayMax = Math::Vector::Vector4(0.0f, 0.05f, 0.1f, 0.01f);
	emit.colorDecayMin = Math::Vector::Vector4(0.0f, 0.05f, 0.1f, 0.01f);
	emit.scaleSizeMax = Math::Vector::Vector3(0.1f, 0.0f, 1.0f);
	emit.scaleSizeMin = Math::Vector::Vector3(0.2f, 0.0f, 1.0f);
}

void WallHitParticle::Update()
{
	particle_->Update();
}

void WallHitParticle::Emit(Math::Vector::Vector3 pos, Math::Vector::Vector3 velo)
{
	auto& emit = boxEmitter_->GetEmitParam()[0];
	emit.count = 10;
	emit.translate = pos;
	emit.velocityMax = velo;
	emit.velocityMin = velo;
	this->boxEmitter_->Update();
	this->boxEmitter_->Emit(particle_);
	emit.count = 0;
}
