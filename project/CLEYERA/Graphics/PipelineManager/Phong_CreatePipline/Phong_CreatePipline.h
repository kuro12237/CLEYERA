#pragma once
#include"Graphics/PipelineManager/StructGraphicsPipline.h"
#include"CreateGraphicsPiplineFanc.h"
#include"ShaderManager.h"

/// <summary>
/// Phong�p�C�v���C���쐻�֐�
/// </summary>
class Phong_CreatePipline
{
public:

	static Phong_CreatePipline* GetInstance();

	void Initialize();
	/// <summary>
    /// Phong���C�e�B���O�̖@���}�b�s���O���f���p�p�C�v���C���X�e�[�g�I�u�W�F�N�g���쐬����֐�
    /// </summary>
	SPSOProperty CreatePhongNormalModel(SShaderMode shader);

	/// <summary>
	/// �f�B�]���u�G�t�F�N�g�t���@���}�b�s���O���f���p�p�C�v���C���X�e�[�g�I�u�W�F�N�g���쐬����֐�
	/// </summary>
	SPSOProperty CreateDissolveNormalModel(SShaderMode shader);

	/// <summary>
	/// �T�u�T�[�t�F�X�E�X�L���^�����O���f���p�p�C�v���C���X�e�[�g�I�u�W�F�N�g���쐬����֐�
	/// </summary>
	SPSOProperty CreateSubsurfaceModel(SShaderMode shader);

	/// <summary>
	/// �C���X�^���V���O���f���p�p�C�v���C���X�e�[�g�I�u�W�F�N�g���쐬����֐�
	/// </summary>
	SPSOProperty CreateInstancingModel(SShaderMode shader);

	/// <summary>
	/// �X�L�j���O���f���p�p�C�v���C���X�e�[�g�I�u�W�F�N�g���쐬����֐�
	/// </summary>
	SPSOProperty CreateSkinningModel(SShaderMode shader);


private:
	ComPtr<ID3D12Device>device = nullptr;
	ComPtr<ID3D12GraphicsCommandList>commandList_ = nullptr;
};
