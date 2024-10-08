#include "TitleFireParticle.h"

TitleFireParticle* TitleFireParticle::GetInstance()
{
    static TitleFireParticle instance;
    return &instance;
}

void TitleFireParticle::Initialize()
{
	if (InitializeLock_)
	{
		return;
	}	InitializeLock_ = true;
	texHandle_ = TextureManager::LoadDDSTexture("GameObject/cloud/cloud.dds");
	particle_ = make_unique<Particle::GpuParticle>();
	particle_->Create(1, name_);
	particle_->SetTexhandle(texHandle_);
	emitter_ = make_unique<Particle::ParticleEmitter<Particle::EmitType::BoxParam>>();
	emitter_->CreateType(particle_);
}

void TitleFireParticle::Update()
{
	emitter_->Update();

	particle_->CallBarrier();
	particle_->Update();
}

void TitleFireParticle::Draw()
{
	particle_->Draw();
	emitter_->SpownDraw();
}

void TitleFireParticle::ImGuiUpdate()
{
	emitter_->ImGuiUpdate();
}

void TitleFireParticle::Emit()
{
	emitter_->Emit(particle_);
}
