#pragma once
#include"Particle/GpuParticle.h"

class ParticleEmitter;
class IEmitterState
{
public:
	virtual ~IEmitterState() {};

	virtual void Create(ParticleEmitter* e) = 0;;

	virtual void Update(ParticleEmitter* e) = 0;

	virtual void Emit() = 0;

	virtual void Dispatch(unique_ptr<Particle::GpuParticle>& particle) = 0;

private:

};

