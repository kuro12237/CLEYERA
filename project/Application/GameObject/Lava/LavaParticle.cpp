#include "LavaParticle.h"

void LavaParticle::Initialize()
{
	this->name_ = "LavaParticle";

	uint32_t modelHandle = Engine::Manager::ModelManager::LoadObjectFile("DfCube");
	this->Create(modelHandle);

	auto& control = emitter_->GetControlParam()[0];
	control.useFlag_ = true;

	auto& emit = emitter_->GetEmitParam()[0];
	emit.count = 10;
	lavaScale_.y = 0.0f;

	emit.sizeMax = lavaScale_;
	emit.sizeMin = Math::Vector::Multiply(lavaScale_, -1.0f);
	emit.velocityMax = Math::Vector::Vector3(0.0f, 0.01f, 0.0f);
	emit.velocityMin = Math::Vector::Vector3(0.0f, 0.1f, 0.0f);
	emit.colorDecayMax = Math::Vector::Vector4(0.0f, 0.05f, 0.1f, 0.01f);
	emit.colorDecayMin = Math::Vector::Vector4(0.0f, 0.05f, 0.1f, 0.01f);
	emit.scaleSizeMax = Math::Vector::Vector3(0.1f, 0.0f, 1.0f);
	emit.scaleSizeMin = Math::Vector::Vector3(0.2f, 0.0f, 1.0f);
}

void LavaParticle::Update()
{
	auto& emit = emitter_->GetEmitParam()[0];

	if (p_LavaPos_)
	{
		emit.translate= *p_LavaPos_;
	}
	particle_->CallBarrier();
	emitter_->Update();
	emitter_->Emit(particle_);
	particle_->CallBarrier();
	particle_->Update();
}
