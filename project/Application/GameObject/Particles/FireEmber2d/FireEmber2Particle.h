#pragma once
#include"Particle/GpuParticle.h"
#include"Particle/Emitter/ParticleEmitter.h"
#include"Graphics/TextureManager/TextureManager.h"

class FireEmber2dParticle
{
public:
	FireEmber2dParticle() {};
	~FireEmber2dParticle() {};

	void Initialize();

	void Update();

	void Draw();

	void ImGuiUpdate();

	void ClearEmitter(uint32_t index) { emitter_->Clear(index); }

#pragma region Get
	Particle::ParticleEmitter<Particle::EmitType::BoxParam>* GetEmitter() { return emitter_.get(); };
#pragma endregion

private:

	bool InitializeLock_ = false;
	string name_ = "FireEmberParticle2d";
	uint32_t texHandle_ = 0;

	unique_ptr<Particle::GpuParticle>particle_ = nullptr;
	unique_ptr<Particle::ParticleEmitter<Particle::EmitType::BoxParam>>emitter_ = nullptr;

private:

};
