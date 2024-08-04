#pragma once
#include"WorldTransform.h"
#include"Particle/Emitter/Draw/IParticleEmitDraw.h"

class ParticleEmitDraw
{
public:
	ParticleEmitDraw() {};
	~ParticleEmitDraw() {};

	void Initialize(string name);

	void Draw(const WorldTransform &w);

private:

	unique_ptr<IParticleEmitDraw>sphere_ = nullptr;

};