#include "CharacterDeadParticle.h"

CharacterDeadParticle* CharacterDeadParticle::GetInstance()
{
    static CharacterDeadParticle instance;
    return &instance;
}

void CharacterDeadParticle::Initialize()
{
    if (InitializeLock_)
    {
        return;
    }
    InitializeLock_ = true;
    texHandle_ = TextureManager::LoadPngTexture("smoke.png");

    particle_ = make_unique<Particle::GpuParticle>();
    particle_->Create(1,name_);
    particle_->SetTexhandle(texHandle_);

    emitter_ = make_unique<Particle::ParticleEmitter<Particle::EmitType::BoxParam>>();
    emitter_->CreateType(particle_);
    auto& emit1 = emitter_->GetControlParam()[0];
    emit1.useFlag_ = true;

}

void CharacterDeadParticle::Update()
{
    emitter_->Emit(particle_);
    emitter_->Update();
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
