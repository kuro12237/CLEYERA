#pragma once
#include"Particle/GpuParticle.h"

namespace Particle {
	class ParticleEmitter;

	class IEmitterState
	{
	public:
		virtual ~IEmitterState() {};

		virtual void Create(Particle::ParticleEmitter* e) = 0;;

		virtual void Update(Particle::ParticleEmitter* e) = 0;

		virtual void Emit() = 0;

		virtual void Dispatch(unique_ptr<Particle::GpuParticle>& particle) = 0;

		virtual void SpownDraw() = 0;
	private:

	};
}

