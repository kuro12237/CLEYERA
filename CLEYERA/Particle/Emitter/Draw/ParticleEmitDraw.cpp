#include "ParticleEmitDraw.h"

ParticleEmitDraw* ParticleEmitDraw::GetInstance()
{
    static ParticleEmitDraw instance;
    return &instance;
}

void ParticleEmitDraw::Initialize()
{
    sphere_ = make_unique<IParticleEmitDraw>();
    sphere_->Create(SPHERE);
}

void ParticleEmitDraw::SphereDraw(const WorldTransform& w)
{ 
    sphere_->Draw(w);
}
