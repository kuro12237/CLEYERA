#include "FireParticle.h"

void FireParticle::Initialize()
{
	if (InitializeLock_)
	{
		return;
	}	InitializeLock_ = true;

	texHandle_ = TextureManager::LoadPngTexture("explosionSmoke.png");
	particle_ = make_unique<Particle::GpuParticle>();
	particle_->Create(1, name_);
	particle_->SetTexhandle(texHandle_);
	emitter_ = make_unique<Particle::ParticleEmitter<Particle::EmitType::BoxParam>>();
	emitter_->CreateType(particle_);
}

void FireParticle::Update()
{
	emitter_->Update();

	particle_->CallBarrier();
	particle_->Update();
}

void FireParticle::Draw()
{
	particle_->Draw();
	emitter_->SpownDraw();
}

void FireParticle::ImGuiUpdate()
{
	emitter_->ImGuiUpdate();
}

void FireParticle::Emit()
{
	emitter_->Emit(particle_);
}
