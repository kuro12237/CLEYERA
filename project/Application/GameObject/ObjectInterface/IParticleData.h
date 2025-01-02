#pragma once
#include"Particle/GpuParticle.h"
#include"Particle/Emitter/ParticleEmitter.h"
#include"Graphics/TextureManager/TextureManager.h"
#include"GameObject/ObjectInterface/IJsonHandler.h"


class IParticleData :public IJsonHandler
{
public:
	IParticleData() {};
	virtual ~IParticleData() {};

	virtual void Initialize() = 0;

	virtual void Update();


	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// Emitterのパラメーターを初期化
	/// </summary>
	/// <param name="index"></param>
	void ClearEmitter(uint32_t index) { emitter_->Clear(index); }

	/// <summary>
	/// ImGui更新
	/// </summary>
	void ImGuiUpdate();

#pragma region Get

	Engine::Particle::ParticleEmitter<Engine::Particle::EmitType::BoxParam>* GetEmitter() { return emitter_.get(); };
	Engine::Particle::GpuParticle* GetParticle() { return particle_.get(); };
#pragma endregion

protected:

	/// <summary>
	/// パーティクル作成
	/// </summary>
	void Create(uint32_t modelHandle = 0);

	void CreateParamJson();

	void UpdateParamJson();

	string name_ = "";
	uint32_t texHandle_ = 0;

	unique_ptr<Engine::Particle::GpuParticle>particle_ = nullptr;
	unique_ptr<Engine::Particle::ParticleEmitter<Engine::Particle::EmitType::BoxParam>>emitter_ = nullptr;

private:
	bool isWriteEmitFileParam_ = false;
};