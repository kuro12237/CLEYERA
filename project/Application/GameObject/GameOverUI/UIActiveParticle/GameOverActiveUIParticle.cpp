#include "GameOverActiveUIParticle.h"

void GameOverActiveUIParticle::Initialize()
{
	texHandle_ = TextureManager::LoadPngTexture("circle.png");
	particle_ = make_unique<Particle::GpuParticle>();
	particle_->Create(1, name_);
	particle_->SetDrawMode(Particle::mode_2d);

	particle_->SetTexhandle(texHandle_);
	emitter_ = make_unique<Particle::ParticleEmitter<Particle::EmitType::BoxParam>>();
	emitter_->CreateType(particle_);

	emitter_->GetControlParam()[0].useFlag_ = true;
	emitter_->GetEmitParam()[0].count = 1;

}

void GameOverActiveUIParticle::Update()
{
	emitter_->ImGuiUpdate();

	emitter_->Emit(particle_);
	emitter_->Update();

	particle_->CallBarrier();
	particle_->Update();
}

void GameOverActiveUIParticle::Draw()
{
	particle_->Draw();
}
