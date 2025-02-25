#pragma once

#include"Particle/GpuParticle.h"
#include"Particle/Emitter/ParticleEmitter.h"
#include"Graphics/TextureManager/TextureManager.h"
#include"GameObject/ObjectInterface/ParticleComponent.h"

/// <summary>
/// 爆発時のパーティクル
/// </summary>
class TitleNameParticle :public ParticleComponent
{
public:
	TitleNameParticle() {};
	~TitleNameParticle() {};

	void Initialize()override;

	void Update()override;

private:

};