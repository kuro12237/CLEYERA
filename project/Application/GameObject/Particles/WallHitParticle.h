#pragma once

#include"Particle/GpuParticle.h"
#include"Particle/Emitter/ParticleEmitter.h"
#include"Graphics/TextureManager/TextureManager.h"
#include"GameObject/ObjectInterface/IParticleData.h"

/// <summary>
/// 壁に当たった時のパーティクル
/// </summary>
class WallHitParticle :public IParticleData
{
public:
	WallHitParticle() {};
	~WallHitParticle() {};

	void Initialize()override;

	void Update()override;

	void Emit(Math::Vector::Vector3 pos,Math::Vector::Vector3 velo);

private:


};