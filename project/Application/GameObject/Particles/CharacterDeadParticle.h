#pragma once
#include"Particle/GpuParticle.h"
#include"Particle/Emitter/ParticleEmitter.h"
#include"Graphics/TextureManager/TextureManager.h"

/// <summary>
/// キャラクターが死んだときのパーティクル
/// </summary>
class CharacterDeadParticle
{
public:

	static CharacterDeadParticle * GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// ImGui更新
	/// </summary>
	void ImGuiUpdate();

	/// <summary>
	/// エミッターの一部をクリア
	/// </summary>
	/// <param name="index"></param>
	void ClearEmitter(uint32_t index) { emitter_->Clear(index); }

	void Emit(){emitter_->Emit(particle_);}

#pragma region Get
	Engine::Particle::ParticleEmitter<Engine::Particle::EmitType::BoxParam>*GetEmitter() { return emitter_.get(); };
#pragma endregion

private:
	bool initializeLock_ = false;
	string name_ = "CharacterDeadParticle";
	uint32_t texHandle_ = 0;

	unique_ptr<Engine::Particle::GpuParticle>particle_ = nullptr;
	unique_ptr<Engine::Particle::ParticleEmitter<Engine::Particle::EmitType::BoxParam>>emitter_ = nullptr;

	CharacterDeadParticle() = default;
	~CharacterDeadParticle() = default;
	CharacterDeadParticle(const CharacterDeadParticle&) = delete;
	const CharacterDeadParticle& operator=(const CharacterDeadParticle&) = delete;
};

