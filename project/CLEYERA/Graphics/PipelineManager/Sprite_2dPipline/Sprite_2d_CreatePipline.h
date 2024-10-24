#pragma once
#include"Graphics/PipelineManager/StructGraphicsPipline.h"
#include"CreateGraphicsPiplineFanc.h"
#include"ShaderManager.h"

/// <summary>
/// 2d�̃p�C�v���C���쐻�֐�
/// </summary>
class Sprite_2d_CreatePipline
{
public:

	static Sprite_2d_CreatePipline* GetInstance();

	void Initialize();
	/// <summary>
    /// �ʏ�`��p�̃p�C�v���C���X�e�[�g�I�u�W�F�N�g���쐬����֐�
    /// </summary>
	SPSOProperty CreateNone(SShaderMode shader);

	/// <summary>
	/// ���Z�����`��p�̃p�C�v���C���X�e�[�g�I�u�W�F�N�g���쐬����֐�
	/// </summary>
	SPSOProperty CreateAdd(SShaderMode shader);

	/// <summary>
	/// ���Z�����`��p�̃p�C�v���C���X�e�[�g�I�u�W�F�N�g���쐬����֐�
	/// </summary>
	SPSOProperty CreateSubtract(SShaderMode shader);

	/// <summary>
	/// ��Z�����`��p�̃p�C�v���C���X�e�[�g�I�u�W�F�N�g���쐬����֐�
	/// </summary>
	SPSOProperty CreateMultiply(SShaderMode shader);

	/// <summary>
	/// �X�N���[�������`��p�̃p�C�v���C���X�e�[�g�I�u�W�F�N�g���쐬����֐�
	/// </summary>
	SPSOProperty CreateScreen(SShaderMode shader);

	/// <summary>
	/// �f�B�]���u�G�t�F�N�g�i�ʏ�`��j�p�̃p�C�v���C���X�e�[�g�I�u�W�F�N�g���쐬����֐�
	/// </summary>
	SPSOProperty CreateDissolveNone(SShaderMode shader);

	/// <summary>
	/// �p�[�����m�C�Y�G�t�F�N�g�p�̃p�C�v���C���X�e�[�g�I�u�W�F�N�g���쐬����֐�
	/// </summary>
	SPSOProperty CreatePerlinNoise(SShaderMode shader);

private:
	ComPtr<ID3D12Device>device = nullptr;
	ComPtr<ID3D12GraphicsCommandList>commandList_ = nullptr;
};

