#pragma once
#include"WorldTransform.h"

#include"Particle/SParticle.h"
#include"CameraData.h"

class Particle;
class IParticleState
{
public:
	
	virtual ~IParticleState() {};

	virtual void Initialize(Particle *state) = 0;

	virtual void Draw(Particle *state, list<Particle_param>param,CameraData viewprojection) = 0;

private:

};

