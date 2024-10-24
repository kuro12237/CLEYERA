#pragma once
#include"StructGraphicsPipline.h"
#include"CreateGraphicsPiplineFanc.h"
#include"ShaderManager.h"

/// <summary>
/// GPU�p�C�v���C���쐻�֐�
/// </summary>
class CreateGpuParticle
{
public:
	/// <summary>
/// GPU�p�[�e�B�N���̏������p�p�C�v���C���X�e�[�g�I�u�W�F�N�g���쐬����֐�
/// </summary>
	static SPSOProperty CreateGpuParticle_Init(ComPtr<ID3D12Device>device, Engine::Base::DX::Commands commands, SShaderMode shader);

	/// <summary>
	/// �`��Ȃ���GPU�p�[�e�B�N���p�p�C�v���C���X�e�[�g�I�u�W�F�N�g���쐬����֐�
	/// </summary>
	static SPSOProperty CreateGpuParticle_NoneDraw(ComPtr<ID3D12Device>device, Engine::Base::DX::Commands commands, SShaderMode shader);

	/// <summary>
	/// ���Z�`����s��GPU�p�[�e�B�N���p�p�C�v���C���X�e�[�g�I�u�W�F�N�g���쐬����֐�
	/// </summary>
	static SPSOProperty CreateGpuParticle_AddDraw(ComPtr<ID3D12Device>device, Engine::Base::DX::Commands commands, SShaderMode shader);

	/// <summary>
	/// �f�B�]���u���ʕt����GPU�p�[�e�B�N���p�p�C�v���C���X�e�[�g�I�u�W�F�N�g���쐬����֐�
	/// </summary>
	static SPSOProperty CreateGpuParticle_DissolveNoneDraw(ComPtr<ID3D12Device>device, Engine::Base::DX::Commands commands, SShaderMode shader);

	/// <summary>
	/// GPU�p�[�e�B�N���̍X�V�p�p�C�v���C���X�e�[�g�I�u�W�F�N�g���쐬����֐�
	/// </summary>
	static SPSOProperty CreateGpuParticle_Update(ComPtr<ID3D12Device>device, Engine::Base::DX::Commands commands, SShaderMode shader);

	/// <summary>
	/// ���`�G�~�b�^�[������GPU�p�[�e�B�N���p�p�C�v���C���X�e�[�g�I�u�W�F�N�g���쐬����֐�
	/// </summary>
	static SPSOProperty CreateGpuParticcle_Emitter_Sphere(ComPtr<ID3D12Device>device, Engine::Base::DX::Commands commands, SShaderMode shader);

	/// <summary>
	/// �{�b�N�X�`�G�~�b�^�[������GPU�p�[�e�B�N���p�p�C�v���C���X�e�[�g�I�u�W�F�N�g���쐬����֐�
	/// </summary>
	static SPSOProperty CreateGpuParticcle_Emitter_Box(ComPtr<ID3D12Device>device, Engine::Base::DX::Commands commands, SShaderMode shader);

	/// <summary>
	/// �z���t�B�[���h������GPU�p�[�e�B�N���p�p�C�v���C���X�e�[�g�I�u�W�F�N�g���쐬����֐�
	/// </summary>
	static SPSOProperty CreateGpuParticle_Field_Suction(ComPtr<ID3D12Device>device, Engine::Base::DX::Commands commands, SShaderMode shader);

private:

};
