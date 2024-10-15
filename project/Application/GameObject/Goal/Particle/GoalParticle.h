#pragma once
#include"Particle/GpuParticle.h"
#include"Particle/Emitter/ParticleEmitter.h"
#include"Particle/Field/ParticleField.h"
#include"Graphics/TextureManager/TextureManager.h"
#include"Utility/ColorConverter/ColorConverter.h"

class GoalParticle
{
public:

	static GoalParticle* GetInstance();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ImGui�X�V
	/// </summary>
	void ImGuiUpdate();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// emitter,field,particlle�̒l���N���A
	/// </summary>
	void Clear() { particle_->Clear(), emitter_->AllClear(), field_->AllClear(); }

#pragma region Get
	Particle::ParticleEmitter<Particle::EmitType::Circle>* GetEmitters() { return emitter_.get(); }
	Particle::GpuParticle* GetParticle() { return  particle_.get(); }
	Particle::ParticleField<Particle::FieldType::FieldSuction>* GetField() { return field_.get(); }
#pragma endregion

private:

	bool InitializeLock_ = false;

	uint32_t texHandle_ = 0;
	unique_ptr<Particle::GpuParticle>particle_ = nullptr;
	unique_ptr<Particle::ParticleEmitter<Particle::EmitType::Circle>>emitter_ = nullptr;
	unique_ptr<Particle::ParticleField<Particle::FieldType::FieldSuction>>field_ = nullptr;

	string name_ = "";
};
