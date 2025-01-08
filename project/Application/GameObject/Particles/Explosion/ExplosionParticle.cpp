#include "ExplosionParticle.h"

void ExplosionParticle::Initialize()
{
	this->name_ = "ExplosionParticle";

	uint32_t modelHandle = Engine::Manager::ModelManager::LoadObjectFile("DfCube");
	this->Create(modelHandle);
	this->particle_->SetMode(SpriteMode::BlendAdd);

	auto& control = boxEmitter_->GetControlParam();
	control[0].useFlag_ = true;
	control[1].useFlag_ = true;

	this->GetLoadDatas();
}

void ExplosionParticle::Update()
{
	boxEmitter_->Update();
	boxEmitter_->Emit(particle_);
	particle_->CallBarrier();
	particle_->Update();
}


