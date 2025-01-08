#include "LavaParticle.h"

void LavaParticle::Initialize()
{
	this->name_ = "LavaParticle";

	uint32_t modelHandle = Engine::Manager::ModelManager::LoadObjectFile("DfCube");
	this->Create(modelHandle);

	auto& control = boxEmitter_->GetControlParam()[0];
	control.useFlag_ = true;

	auto& emit = boxEmitter_->GetEmitParam()[0];
	emit.count = 10;
	lavaScale_.y = 0.0f;

	emit.sizeMax = lavaScale_;
	emit.sizeMin = Math::Vector::Multiply(lavaScale_, -1.0f);
}

void LavaParticle::Update()
{
	auto& emit = boxEmitter_->GetEmitParam()[0];

	if (p_LavaPos_)
	{
		emit.translate= *p_LavaPos_;
	}
	particle_->CallBarrier();
	boxEmitter_->Update();
	boxEmitter_->Emit(particle_);
	particle_->CallBarrier();
	particle_->Update();
}
