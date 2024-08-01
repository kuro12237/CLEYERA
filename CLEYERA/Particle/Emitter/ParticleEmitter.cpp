#include "ParticleEmitter.h"

void ParticleEmitter::CreateType(unique_ptr<IEmitterState> state, unique_ptr<Particle::GpuParticle>& particle)
{
	sphere_.resize(particle->GetNum());
	type_ = move(state);
	emitName_ = particle->GetName();
	type_->Create(this);
}

void ParticleEmitter::Update()
{
	type_->Update(this);
}

void ParticleEmitter::Emit(unique_ptr<Particle::GpuParticle>& particle)
{
	type_->Dispatch(particle);
}
