#pragma once
#include"Particle/GpuParticle.h"
#include"Particle/Emitter/ParticleEmitter.h"
#include"Graphics/TextureManager/TextureManager.h"

/// <summary>
/// �L�����N�^�[�̓������̃p�[�e�B�N��
/// </summary>
class CharacterMoveParticle
{
public:
	static CharacterMoveParticle* GetInstance();

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
	/// Emitter�̃p�����[�^�[��������
	/// </summary>
	/// <param name="index"></param>
	void ClearEmitter(uint32_t index) { emitter_->Clear(index); }

	/// <summary>
	/// �p�[�e�B�N���𕦂�����
	/// </summary>
	void Emit();

#pragma region Get
	Engine::Particle::ParticleEmitter<Engine::Particle::EmitType::BoxParam>* GetEmitter() { return emitter_.get(); };
#pragma endregion

private:

	bool InitializeLock_ = false;
	string name_ = "CharacterMoveParticle";
	uint32_t texHandle_ = 0;

	unique_ptr<Engine::Particle::GpuParticle>particle_ = nullptr;
	unique_ptr<Engine::Particle::ParticleEmitter<Engine::Particle::EmitType::BoxParam>>emitter_ = nullptr;

	CharacterMoveParticle() = default;
	~CharacterMoveParticle() = default;
	CharacterMoveParticle(const CharacterMoveParticle&) = delete;
	const CharacterMoveParticle& operator=(const CharacterMoveParticle&) = delete;
};

