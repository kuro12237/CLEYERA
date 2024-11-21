#pragma once
#include"Particle/GpuParticle.h"
#include"Particle/Emitter/ParticleEmitter.h"
#include"Graphics/TextureManager/TextureManager.h"

/// <summary>
/// �L�����N�^�[�����񂾂Ƃ��̃p�[�e�B�N��
/// </summary>
class CharacterDeadParticle
{
public:

	static CharacterDeadParticle * GetInstance();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// ImGui�X�V
	/// </summary>
	void ImGuiUpdate();

	/// <summary>
	/// �G�~�b�^�[�̈ꕔ���N���A
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

