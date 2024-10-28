#pragma once
#include"Particle/GpuParticle.h"
#include"Particle/Emitter/ParticleEmitter.h"
#include"Graphics/TextureManager/TextureManager.h"

/// <summary>
/// �I�����Ă���UI�̃p�[�e�B�N��
/// </summary>
class GameOverActiveUIParticle
{
public:
	GameOverActiveUIParticle() {};
	~GameOverActiveUIParticle() {};

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �\��
	/// </summary>
	void Draw();

#pragma region Set
	void SetEmitParam(const Math::Vector::Vector3& t) { emitter_->GetEmitParam()[0].translate = t; }
#pragma endregion

private:

	string name_ = "GameOverActiveUIParticle";
	uint32_t texHandle_ = 0;

	unique_ptr<Particle::GpuParticle>particle_ = nullptr;
	unique_ptr<Particle::ParticleEmitter<Particle::EmitType::BoxParam>>emitter_ = nullptr;


};
