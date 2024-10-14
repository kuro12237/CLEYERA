#include "FireEmber2Particle.h"

void FireEmber2dParticle::Initialize()
{
    texHandle_ = TextureManager::LoadPngTexture("FireEmber.png");

    particle_ = make_unique<Particle::GpuParticle>();
    particle_->Create(1, name_);
    particle_->SetTexhandle(texHandle_);
    particle_->SetDrawMode(Particle::mode_2d);
    particle_->SetMode(BlendAdd);
    particle_->Set2dSize(TextureManager::GetTextureSize(texHandle_));

    emitter_ = make_unique<Particle::ParticleEmitter<Particle::EmitType::BoxParam>>();
    emitter_->CreateType(particle_);


}

void FireEmber2dParticle::Update()
{
    emitter_->Update();
    emitter_->Emit(particle_);
    particle_->CallBarrier();
    particle_->Update();
}

void FireEmber2dParticle::Draw()
{

    particle_->Draw();
    emitter_->SpownDraw();
}

void FireEmber2dParticle::ImGuiUpdate()
{

    emitter_->ImGuiUpdate();
}
