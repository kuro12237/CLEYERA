#pragma once
#include"Particle/GpuParticle.h"
#include"Particle/Emitter/ParticleEmitter.h"
#include"Graphics/TextureManager/TextureManager.h"

class CharacterDeadParticle
{
public:
	
	static CharacterDeadParticle * GetInstance();

	void Initialize();

	void Update();

	void Draw();

	void ImGuiUpdate();

private:

	bool InitializeLock_ = false;
	string name_ = "CharacterDeadParticle";
	uint32_t texHandle_ = 0;

	unique_ptr<Particle::GpuParticle>particle_ = nullptr;
	unique_ptr<Particle::ParticleEmitter<Particle::EmitType::BoxParam>>emitter_ = nullptr;

	CharacterDeadParticle() = default;
	~CharacterDeadParticle() = default;
	CharacterDeadParticle(const CharacterDeadParticle&) = delete;
	const CharacterDeadParticle& operator=(const CharacterDeadParticle&) = delete;
};

