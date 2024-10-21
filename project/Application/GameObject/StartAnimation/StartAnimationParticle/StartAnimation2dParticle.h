#pragma once

#include"Particle/GpuParticle.h"
#include"Particle/Emitter/ParticleEmitter.h"
#include"Graphics/TextureManager/TextureManager.h"

/// <summary>
/// 2d�̉�����o����̃p�[�e�B�N��
/// </summary>
class StartAnimation2dParticle
{
public:
	StartAnimation2dParticle() {};
	~StartAnimation2dParticle() {};

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
	/// �ԍ��̃G�~�b�^�[���N���A
	/// </summary>
	/// <param name="index"></param>
	void ClearEmitter(uint32_t index) { emitter_->Clear(index); }

	/// <summary>
	/// �p�[�e�B�N���𕰂�
	/// </summary>
	void Emit(bool f) { emitter_->GetControlParam()[0].useFlag_ = f; }

#pragma region Set
	void SetUseFlag(const bool& f) { emitter_->GetControlParam()[0].useFlag_ = f; }
	void SetSpownCount(const uint32_t& count) { emitter_->GetEmitParam()[0].count = count; }
#pragma endregion

#pragma region Get
	Particle::ParticleEmitter<Particle::EmitType::BoxParam>* GetEmitter() { return emitter_.get(); };
#pragma endregion

private:

	bool InitializeLock_ = false;
	string name_ = "StartAnimation2dParticle";
	uint32_t texHandle_ = 0;

	unique_ptr<Particle::GpuParticle>particle_ = nullptr;
	unique_ptr<Particle::ParticleEmitter<Particle::EmitType::BoxParam>>emitter_ = nullptr;

};
