#include "GameOverActiveUIParticle.h"

void GameOverActiveUIParticle::Initialize()
{
	texHandle_ = TextureManager::LoadPngTexture("circle.png");
	particle_ = make_unique<Particle::GpuParticle>();
	particle_->Create(1, name_);
	particle_->SetDrawMode(Particle::mode_2d);

	Math::Vector::Vector2 texSize = TextureManager::GetTextureSize(texHandle_);
	particle_->SetTexhandle(texHandle_);
	particle_->Set2dSize(texSize);
	texSize.x *= -0.5f;
	texSize.y *= -0.5f;
	particle_->SetPos(texSize);

	emitter_ = make_unique<Particle::ParticleEmitter<Particle::EmitType::BoxParam>>();
	emitter_->CreateType(particle_);

	auto& emit = emitter_->GetEmitParam()[0];
	auto& control = emitter_->GetControlParam()[0];

	emit.sizeMin = { -64.0f,-36.0f,0.0f };
	emit.sizeMax = { 64.0f,36.0f,0.0f };

	emit.scaleSizeMin = { 0.0625f,0.125f,0.125f };
	emit.scaleSizeMax = { 0.125f,0.0625f,0.125f };

	emit.velocityMin = { -1.5f,-1.0f,0.0f };
	emit.velocityMax = { 1.5f,1.0f,0.0f };
	control.frequencyTime = 0.2f;
	emit.count = 4;
	control.useFlag_ = true;
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
