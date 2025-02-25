#pragma once

#include"Particle/GpuParticle.h"
#include"Particle/Emitter/ParticleEmitter.h"
#include"Graphics/TextureManager/TextureManager.h"
#include"GameObject/ObjectInterface/ParticleComponent.h"

/// <summary>
/// 爆発時のパーティクル
/// </summary>
class ExplosionParticle :public ParticleComponent
{
public:
	ExplosionParticle() {};
	~ExplosionParticle() {};

	void Initialize()override;

	void Update()override;

	void Emit(Math::Vector::Vector3 pos, Math::Vector::Vector3 velo);

private:

};

