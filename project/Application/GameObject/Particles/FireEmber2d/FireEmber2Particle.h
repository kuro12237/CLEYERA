#pragma once
#include"Particle/GpuParticle.h"
#include"Particle/Emitter/ParticleEmitter.h"
#include"Graphics/TextureManager/TextureManager.h"

/// <summary>
/// 2dの下から出る日のパーティクル
/// </summary>
class FireEmber2dParticle
{
public:
	FireEmber2dParticle() {};
	~FireEmber2dParticle() {};

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
	/// Imguiの更新
	/// </summary>
	void ImGuiUpdate();

	/// <summary>
	/// 番号のエミッターをクリア
	/// </summary>
	/// <param name="index"></param>
	void ClearEmitter(uint32_t index) { emitter_->Clear(index); }

	/// <summary>
	/// パーティクルを焚く
	/// </summary>
	void Emit() { emitter_->Emit(particle_); }

#pragma region Set
	void SetUseFlag(const bool& f) { emitter_->GetControlParam()[0].useFlag_ = f; }
#pragma endregion

#pragma region Get
	Particle::ParticleEmitter<Particle::EmitType::BoxParam>* GetEmitter() { return emitter_.get(); };
#pragma endregion

private:

	bool InitializeLock_ = false;
	string name_ = "FireEmberParticle2d";
	uint32_t texHandle_ = 0;

	unique_ptr<Particle::GpuParticle>particle_ = nullptr;
	unique_ptr<Particle::ParticleEmitter<Particle::EmitType::BoxParam>>emitter_ = nullptr;

};
