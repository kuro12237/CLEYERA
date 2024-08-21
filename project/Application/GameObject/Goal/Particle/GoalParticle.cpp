#include "GoalParticle.h"

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
	name_ = "GoalParticle";
	particle_->Create(1,name_);
	emitter_->CreateType(particle_);
}

void GoalParticle::ImGuiUpdate()
{
	emitter_->ImGuiUpdate();
}

void GoalParticle::Update()
{
	emitter_->Update();
	emitter_->Emit(particle_);
	particle_->CallBarrier();
	particle_->Update();
}

void GoalParticle::Draw()
{
	particle_->Draw();
	emitter_->SpownDraw();
}
