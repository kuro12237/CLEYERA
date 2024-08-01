#pragma once
#include"IEmitterState.h"
#include"ParticleEmitter.h"

class EmitterSphere : public IEmitterState
{
public:
	EmitterSphere() {};
	~EmitterSphere() {};

	void Create(ParticleEmitter* e)override;

	void Update(ParticleEmitter* e)override;

	void Dispatch(unique_ptr<Particle::GpuParticle>& particle)override;

	void Emit()override;

private:
	uint32_t max_ = 0;
	unique_ptr<BufferResource<SEmitterSphere>>sphereBuf_ = nullptr;
};
