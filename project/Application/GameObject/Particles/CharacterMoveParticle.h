#pragma once
#include"Particle/GpuParticle.h"
#include"Particle/Emitter/ParticleEmitter.h"
#include"Graphics/TextureManager/TextureManager.h"

class CharacterMoveParticle
{
public:

	static CharacterMoveParticle* GetInstance();

	void Initialize();

	void Update();

	void Draw();

	void ImGuiUpdate();

	void ClearEmitter(uint32_t index) { emitter_->Clear(index); }

	void Emit();

#pragma region Get


	Particle::ParticleEmitter<Particle::EmitType::BoxParam>* GetEmitter() { return emitter_.get(); };


#pragma endregion

private:

	bool InitializeLock_ = false;
	string name_ = "CharacterMoveParticle";
	uint32_t texHandle_ = 0;

	unique_ptr<Particle::GpuParticle>particle_ = nullptr;
	unique_ptr<Particle::ParticleEmitter<Particle::EmitType::BoxParam>>emitter_ = nullptr;

	CharacterMoveParticle() = default;
	~CharacterMoveParticle() = default;
	CharacterMoveParticle(const CharacterMoveParticle&) = delete;
	const CharacterMoveParticle& operator=(const CharacterMoveParticle&) = delete;
};

