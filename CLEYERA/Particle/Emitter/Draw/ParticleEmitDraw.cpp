#include "ParticleEmitDraw.h"

void ParticleEmitDraw::Initialize(string name)
{
    sphere_ = make_unique<IParticleEmitDraw>();
    sphere_->Create(SPHERE,name);
}

void ParticleEmitDraw::Draw(const WorldTransform& w)
{
    sphere_->Draw(w);
}
