#pragma once
#include"Particle/GpuParticle.h"
#include"Particle/Emitter/ParticleEmitter.h"
#include"Graphics/TextureManager/TextureManager.h"
#include"GameObject/ObjectInterface/ParticleComponent.h"

class LavaParticle :public ParticleComponent
{
public:
	LavaParticle() {};
	~LavaParticle() {};

	void Initialize()override;

	void Update()override;

#pragma region Set
	void SetLavaScale(const Math::Vector::Vector3& scale) { lavaScale_ = scale; }
	void SetLavaPos(const Math::Vector::Vector3& pos) { p_LavaPos_ = &pos; }
#pragma endregion


private:

	const Math::Vector::Vector3* p_LavaPos_ = nullptr;
	Math::Vector::Vector3 lavaScale_ = {};

};

