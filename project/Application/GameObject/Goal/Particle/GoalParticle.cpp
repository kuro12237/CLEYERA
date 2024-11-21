#include "GoalParticle.h"

using namespace Engine;
using namespace Engine::Manager;
using namespace Engine::Transform;

GoalParticle* GoalParticle::GetInstance()
{
	static GoalParticle instance;
	return &instance;
}

void GoalParticle::Initialize()
{
	if (InitializeLock_)
	{
		return;
	}
	InitializeLock_ = true;

	particle_ = make_unique<Particle::GpuParticle>();
	emitter_ = make_unique<Particle::ParticleEmitter<Particle::EmitType::Circle>>();
	field_ = make_unique<Particle::ParticleField<Particle::FieldType::FieldSuction>>();
	name_ = "GoalParticle";
	particle_->Create(3, name_);

	texHandle_ = TextureManager::LoadPngTexture("circle.png");
	particle_->SetTexhandle(texHandle_);
	particle_->SetMode(BlendAdd);

	emitter_->CreateType(particle_);
	field_->CreateType(name_ + "Suction");

}

void GoalParticle::ImGuiUpdate()
{
	emitter_->ImGuiUpdate();
	field_->ImGuiUpdate();
}

void GoalParticle::Update()
{
	particle_->CallBarrier();
	emitter_->Update();
	emitter_->Emit(particle_);
	particle_->CallBarrier();
	field_->Update();
	field_->Dispach(particle_.get());
	particle_->CallBarrier();
	particle_->Update();
}

void GoalParticle::Draw()
{
	particle_->Draw();
	emitter_->SpownDraw();
}
