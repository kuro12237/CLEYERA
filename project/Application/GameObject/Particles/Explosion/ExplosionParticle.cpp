#include "ExplosionParticle.h"

void ExplosionParticle::Initialize()
{
	this->name_ = "WallHitParticle";

	uint32_t modelHandle = Engine::Manager::ModelManager::LoadObjectFile("DfCube");
	this->Create(modelHandle);

	auto& control = emitter_->GetControlParam()[0];
	control.useFlag_ = true;

	auto& emit = emitter_->GetEmitParam()[0];
	emit.count = 0;
}

void ExplosionParticle::Update()
{
	emitter_->Update();
	emitter_->Emit(particle_);
	particle_->CallBarrier();
	particle_->Update();
}


