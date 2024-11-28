#include "PlayerDeadParticle.h"

using namespace Engine;
using namespace Engine::Manager;
using namespace Engine::Transform;

void PlayerDeadParticle::Initialize()
{
    texHandle_ = TextureManager::LoadPngTexture("deadEffect.png");

    particle_ = make_unique<Particle::GpuParticle>();
    particle_->Create(1, name_);
    particle_->SetTexhandle(texHandle_);

    emitter_ = make_unique<Particle::ParticleEmitter<Particle::EmitType::BoxParam>>();
    emitter_->CreateType(particle_);
}

void PlayerDeadParticle::Update()
{ 
    emitter_->Update();
    emitter_->Emit(particle_);
    particle_->CallBarrier();
    particle_->Update();
}

void PlayerDeadParticle::Draw()
{
    particle_->Draw();
    emitter_->SpownDraw();
}

void PlayerDeadParticle::ImGuiUpdate()
{
    emitter_->ImGuiUpdate();
}
