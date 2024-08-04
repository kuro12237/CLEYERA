#pragma once
#include"Particle/GpuParticle.h"
#include"Draw/IParticleEmitDraw.h"
#include"Draw/ParticleEmitDraw.h"

namespace Particle {

	class ParticleEmitter;
	class IEmitterState
	{
	public:
		virtual ~IEmitterState() {};

		virtual void Create(Particle::ParticleEmitter* e) = 0;;

		virtual void Update(Particle::ParticleEmitter* e) = 0;

		virtual void Dispatch(unique_ptr<Particle::GpuParticle>& particle) = 0;

		void SpownDraw();

		vector<WorldTransform>& GetWts() { return wTs_; }

	protected:

		void CreateEmitDraw(uint32_t num, string name);

		vector<WorldTransform>wTs_{};
		vector<unique_ptr<ParticleEmitDraw>>draws_{};
	};
}

