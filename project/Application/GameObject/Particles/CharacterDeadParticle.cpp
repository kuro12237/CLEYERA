#include "CharacterDeadParticle.h"


using namespace Engine;
using namespace Engine::Manager;
using namespace Engine::Transform;

CharacterDeadParticle* CharacterDeadParticle::GetInstance()
{
    static CharacterDeadParticle instance;
    return &instance;
}

void CharacterDeadParticle::Initialize()
{
    if (initializeLock_)
    {
        return;
    }
    initializeLock_ = true;
    texHandle_ = TextureManager::LoadPngTexture("circle.png");

    particle_ = make_unique<Particle::GpuParticle>();
    particle_->Create(1,name_);
    particle_->SetTexhandle(texHandle_);

    emitter_ = make_unique<Particle::ParticleEmitter<Particle::EmitType::BoxParam>>();
    emitter_->CreateType(particle_);

}

void CharacterDeadParticle::Update()
{
    emitter_->Update();
    emitter_->Emit(particle_);
    particle_->CallBarrier();
    particle_->Update();
}

void CharacterDeadParticle::Draw()
{
    particle_->Draw();
    emitter_->SpownDraw();
}

void CharacterDeadParticle::ImGuiUpdate()
{
    emitter_->ImGuiUpdate();
}
