#include "StartAnimation2dParticle.h"

void StartAnimation2dParticle::Initialize()
{
    texHandle_ = TextureManager::LoadPngTexture("FireEmber.png");

    particle_ = make_unique<Particle::GpuParticle>();
    particle_->Create(1, name_);
    particle_->SetTexhandle(texHandle_);
    particle_->SetDrawMode(Particle::mode_2d);
    //particle_->SetMode(DissolveNone);
    particle_->Set2dSize(TextureManager::GetTextureSize(texHandle_));
    particle_->SetNoiseTexHandle(TextureManager::LoadPngTexture("GameObject/Noise/Noise.png"));

    emitter_ = make_unique<Particle::ParticleEmitter<Particle::EmitType::BoxParam>>();
    emitter_->CreateType(particle_);

    auto& emit = emitter_->GetEmitParam()[0];
    auto& control = emitter_->GetControlParam()[0];

    emit.translate = { 640.0f,360.0f,0.0f };
    emit.sizeMin = { -64.0f,-64.0f,0.0f };
    emit.sizeMax = { 64.0f,64.0f,0.0f };

    emit.scaleSizeMin = { 0.125f,0.125f,0.125f };

    emit.velocityMin = { -3.0f,-3.0f,0.0f };
    emit.velocityMax = { 3.0f,3.0f,0.0f };
    control.frequencyTime = 0.0f;
    emit.count = 0;
    control.useFlag_ = true;
}

void StartAnimation2dParticle::Update()
{
    emitter_->Update();
    emitter_->Emit(particle_);
    particle_->CallBarrier();
    particle_->Update();
}

void StartAnimation2dParticle::Draw()
{

    particle_->Draw();
}

void StartAnimation2dParticle::ImGuiUpdate()
{
    emitter_->ImGuiUpdate();
}
