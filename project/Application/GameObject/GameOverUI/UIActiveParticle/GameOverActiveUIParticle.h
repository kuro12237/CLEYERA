#pragma once
#include"Particle/GpuParticle.h"
#include"Particle/Emitter/ParticleEmitter.h"
#include"Graphics/TextureManager/TextureManager.h"

/// <summary>
/// 選択しているUIのパーティクル
/// </summary>
class GameOverActiveUIParticle
{
public:
	GameOverActiveUIParticle() {};
	~GameOverActiveUIParticle() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 表示
	/// </summary>
	void Draw();

#pragma region Set
	void SetEmitParam(const Math::Vector::Vector3& t) { emitter_->GetEmitParam()[0].translate = t; }
#pragma endregion

private:

	string name_ = "GameOverActiveUIParticle";
	uint32_t texHandle_ = 0;

	unique_ptr<Engine::Particle::GpuParticle>particle_ = nullptr;
	unique_ptr<Engine::Particle::ParticleEmitter<Engine::Particle::EmitType::BoxParam>>emitter_ = nullptr;


};
