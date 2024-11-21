#pragma once
#include"Particle/GpuParticle.h"
#include"Particle/Emitter/ParticleEmitter.h"
#include"Graphics/TextureManager/TextureManager.h"

/// <summary>
/// �v���C���[�����񂾂Ƃ��̃p�[�e�B�N��
/// </summary>
class PlayerDeadParticle
{
public:

	PlayerDeadParticle() {};
	~PlayerDeadParticle() {  };
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

#pragma region Get
	Engine::Particle::ParticleEmitter<Engine::Particle::EmitType::BoxParam>* GetEmitter() { return emitter_.get(); };
#pragma endregion

private:

	string name_ = "PlayerDeadParticle";
	uint32_t texHandle_ = 0;

	unique_ptr<Engine::Particle::GpuParticle>particle_ = nullptr;
	unique_ptr<Engine::Particle::ParticleEmitter<Engine::Particle::EmitType::BoxParam>>emitter_ = nullptr;

};

