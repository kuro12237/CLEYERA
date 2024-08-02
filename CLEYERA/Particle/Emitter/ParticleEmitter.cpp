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
	sphere_[0].frequency += DeltaTimer(sphere_[0].flame);
	if (sphere_[0].frequency >= sphere_[0].frequencyTime)
	{
		sphere_[0].frequency = 0.0f;
		sphere_[0].emit = 1;
	}
	else
	{
		sphere_[0].emit = 0;
	}

	type_->Update(this);
}

void ParticleEmitter::Emit(unique_ptr<Particle::GpuParticle>& particle)
{
	type_->Dispatch(particle);
}
