#include "FireEmber2Particle.h"

void FireEmber2dParticle::Initialize()
{
    texHandle_ = TextureManager::LoadPngTexture("FireEmber.png");

    particle_ = make_unique<Particle::GpuParticle>();
    particle_->Create(1, name_);
    particle_->SetTexhandle(texHandle_);
    particle_->SetDrawMode(Particle::mode_2d);
    particle_->SetMode(DissolveNone);
    particle_->Set2dSize(TextureManager::GetTextureSize(texHandle_));
    particle_->SetNoiseTexHandle(TextureManager::LoadPngTexture("GameObject/Noise/Noise.png"));

    emitter_ = make_unique<Particle::ParticleEmitter<Particle::EmitType::BoxParam>>();
    emitter_->CreateType(particle_);

    auto& emit = emitter_->GetEmitParam()[0];
    auto& control = emitter_->GetControlParam()[0];

    emit.sizeMin = { 0.0f,720.0f,0.0f };
    emit.sizeMax = { 1280.0f,720.0f,0.0f };

    emit.scaleSizeMin = { 0.125f,0.125f,0.125f};

    emit.velocityMin = { -4.0f,-3.0f,0.0f };
    emit.velocityMax = { 4.0f,-6.0f,0.0f };
    control.frequencyTime = 0.2f;
    emit.count = 4;
    control.useFlag_ = true;
}

void FireEmber2dParticle::Update()
{
    emitter_->Update();
    particle_->CallBarrier();
    particle_->Update();
}

void FireEmber2dParticle::Draw()
{

    particle_->Draw();
    //emitter_->SpownDraw();
}

void FireEmber2dParticle::ImGuiUpdate()
{

    emitter_->ImGuiUpdate();
}
