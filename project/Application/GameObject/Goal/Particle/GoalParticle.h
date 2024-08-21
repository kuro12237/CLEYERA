#pragma once
#include"Particle/GpuParticle.h"
#include"Particle/Emitter/ParticleEmitter.h"

class GoalParticle
{
public:

	static GoalParticle* GetInstance();

	void Initialize();

	void ImGuiUpdate();

	void Update();

	void Draw();

	Particle::ParticleEmitter<Particle::EmitType::Circle>* GetEmitters() { return emitter_.get(); }

private:

	bool InitializeLock_ = false;

	uint32_t texHandle = 0;
	unique_ptr<Particle::GpuParticle>particle_ = nullptr;
	unique_ptr<Particle::ParticleEmitter<Particle::EmitType::Circle>>emitter_ = nullptr;

	string name_;
};
