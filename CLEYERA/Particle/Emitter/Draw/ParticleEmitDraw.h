#pragma once
#include"WorldTransform.h"
#include"Particle/Emitter/Draw/IParticleEmitDraw.h"

class ParticleEmitDraw
{
public:
	ParticleEmitDraw() {};
	~ParticleEmitDraw() {};

	static ParticleEmitDraw* GetInstance();

	void Initialize();

	
	void SphereDraw(const WorldTransform &w);

private:

	unique_ptr<IParticleEmitDraw>sphere_ = nullptr;

};