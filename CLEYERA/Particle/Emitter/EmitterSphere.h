#pragma once
#include"IEmitterState.h"
#include"ParticleEmitter.h"
#include"Draw/ParticleEmitDraw.h"

class EmitterSphere : public Particle::IEmitterState
{
public:
	EmitterSphere() {};
	~EmitterSphere() {};

	void Create(Particle::ParticleEmitter* e)override;

	void Update(Particle::ParticleEmitter* e)override;

	void Dispatch(unique_ptr<Particle::GpuParticle>& particle)override;

	void Emit()override;

	void SpownDraw()override;

private:
	uint32_t max_ = 0;
	vector<WorldTransform> worldTransform_ = {};
	unique_ptr<BufferResource<SEmitterSphere>>sphereBuf_ = nullptr;
};
