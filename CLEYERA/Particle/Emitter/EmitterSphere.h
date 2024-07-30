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

	void Dispatch()override;

	void Emit()override;

private:

	unique_ptr<BufferResource<SEmitterSphere>>sphereBuf_ = nullptr;
};
