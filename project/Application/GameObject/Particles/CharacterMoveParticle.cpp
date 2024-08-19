#include "CharacterMoveParticle.h"

CharacterMoveParticle* CharacterMoveParticle::GetInstance()
{
	static CharacterMoveParticle instance;
	return &instance;
}

void CharacterMoveParticle::Initialize()
{
	if (InitializeLock_)
	{
		emitter_->AllClear();
		return;
	}
	InitializeLock_ = true;
	texHandle_ = TextureManager::LoadPngTexture("GameObject/cloud/cloud.png");
	particle_ = make_unique<Particle::GpuParticle>();
	particle_->Create(1, name_);
	particle_->SetTexhandle(texHandle_);

	emitter_ = make_unique<Particle::ParticleEmitter<Particle::EmitType::BoxParam>>();
	emitter_->CreateType(particle_);
}

void CharacterMoveParticle::Update()
{
	emitter_->Update();
	
	particle_->CallBarrier();
	particle_->Update();
}

void CharacterMoveParticle::Draw()
{
	particle_->Draw();
	emitter_->SpownDraw();
}

void CharacterMoveParticle::ImGuiUpdate()
{
	emitter_->ImGuiUpdate();
}

void CharacterMoveParticle::Emit()
{
	emitter_->Emit(particle_);
}
