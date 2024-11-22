#pragma once
#include"Particle/GpuParticle.h"
#include"Particle/Emitter/ParticleEmitter.h"
#include"Graphics/TextureManager/TextureManager.h"

/// <summary>
/// キャラクターの動く時のパーティクル
/// </summary>
class ClearCoinSplashParticle
{
public:

	ClearCoinSplashParticle() {};
	~ClearCoinSplashParticle() {};

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
	/// Emitterのパラメーターを初期化
	/// </summary>
	/// <param name="index"></param>
	void ClearEmitter(uint32_t index) { emitter_->Clear(index); }

	/// <summary>
	/// パーティクルを沸かせる
	/// </summary>
	void Emit();

#pragma region Get
	Engine::Particle::ParticleEmitter<Engine::Particle::EmitType::BoxParam>* GetEmitter() { return emitter_.get(); };
#pragma endregion

private:

	string name_ = "ClearCoinSplashParticle";
	uint32_t texHandle_ = 0;

	unique_ptr<Engine::Particle::GpuParticle>particle_ = nullptr;
	unique_ptr<Engine::Particle::ParticleEmitter<Engine::Particle::EmitType::BoxParam>>emitter_ = nullptr;

};