#include "ClearCoinSplashParticle.h"

using namespace Engine;
using namespace Engine::Manager;
using namespace Engine::Transform;

void ClearCoinSplashParticle::Initialize()
{
	texHandle_ = TextureManager::LoadPngTexture("GameClear/SphereNoise.png");

	particle_ = make_unique<Particle::GpuParticle>();
	particle_->Create(1, name_);
	particle_->SetTexhandle(texHandle_);

	emitter_ = make_unique<Particle::ParticleEmitter<Particle::EmitType::BoxParam>>();
	emitter_->CreateType(particle_);
}

void ClearCoinSplashParticle::Update()
{
	emitter_->Update();
	particle_->CallBarrier();
	particle_->Update();
}

void ClearCoinSplashParticle::Draw()
{
	particle_->Draw();

	emitter_->SpownDraw();
}

void ClearCoinSplashParticle::ImGuiUpdate()
{
	emitter_->ImGuiUpdate();
}

void ClearCoinSplashParticle::Emit()
{
	emitter_->Emit(particle_);
}
