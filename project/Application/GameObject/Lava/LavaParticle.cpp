#include "LavaParticle.h"

void LavaParticle::Initialize()
{
	this->name_ = "LavaParticle";

	uint32_t modelHandle = Engine::Manager::ModelManager::LoadObjectFile("DfCube");
	this->Create(modelHandle);
}

void LavaParticle::Update()
{
	auto& emit = emitter_->GetEmitParam()[0];
	emit.translate.z = p_LavaPos_->z;

	particle_->CallBarrier();
	emitter_->Update();
	emitter_->Emit(particle_);
	particle_->CallBarrier();
	particle_->Update();
}
