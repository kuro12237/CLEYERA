#pragma once
#include"Particle/GpuParticle.h"
#include"Particle/Emitter/ParticleEmitter.h"
#include"Graphics/TextureManager/TextureManager.h"

/// <summary>
/// ���̃p�[�e�B�N��
/// </summary>
class FireParticle
{
public:

	FireParticle() {};
	~FireParticle() {};

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
	/// Imgui�̍X�V
	/// </summary>
	void ImGuiUpdate();

	/// <summary>
	/// �ԍ��̃G�~�b�^�[���폜
	/// </summary>
	/// <param name="index"></param>
	void ClearEmitter(uint32_t index) { emitter_->Clear(index); }

	/// <summary>
	/// �p�[�e�B�N���𕰂�
	/// </summary>
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

};

