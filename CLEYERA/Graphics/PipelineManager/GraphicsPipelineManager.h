#pragma once
#include"LogManager.h"
#include"DirectXCommon.h"
#include"ShaderManager.h"
#include"StructGraphicsPipline.h"

#include"ModelCreatePipline/ModelCreatePipline.h"
#include"PostProcess/CreatePostProcess.h"


class GraphicsPipelineManager
{
public:

	static GraphicsPipelineManager* GetInstance();

	static void Initialize();
    SPSO GetPso() { return pso; }

#pragma region Set


#pragma endregion

private:

	static void CreateRootSignature(
		ComPtr<ID3D12Device> device,
		D3D12_ROOT_SIGNATURE_DESC& descriptionRootSignature,
		SPSOProperty& result
	);

	/// <summary>
	/// InputElement�̐ݒ�
	/// </summary>
	/// <param name="inputElementDescs"></param>
	/// <param name="SemanticName"></param>
	/// <param name="SemanticIndex"></param>
	/// <param name="Format"></param>
	/// <param name="AlignedByteOffset"></param>
	static void SettingInputElementDesc(
		D3D12_INPUT_ELEMENT_DESC &inputElementDescs,
		LPCSTR SemanticName,
		UINT SemanticIndex,
		DXGI_FORMAT Format,
		UINT AlignedByteOffset
		);

	/// <summary>
	/// �u�����h���[�h�̐ݒ�
	/// </summary>
	/// <param name="blenddesc"></param>
	/// <param name="mode"></param>
	static void SettingBlendState(
		D3D12_RENDER_TARGET_BLEND_DESC& blenddesc,
		BlendMode mode);

	/// <summary>
	/// ���X�^���C�U�[�̐ݒ�
	/// </summary>
	/// <param name="rasterizerDesc"></param>
	/// <param name="CullMode : �ǂ̌����ɕ\�����邩"></param>
	/// <param name="FillMode : �h��Ԃ���"></param>
	static void SettingRasterizer(
		D3D12_RASTERIZER_DESC& rasterizerDesc,
		D3D12_CULL_MODE CullMode,
		D3D12_FILL_MODE FillMode
	);

	/// <summary>
	/// �[�x�̐ݒ�
	/// </summary>
	/// <param name="despthStencilDesc"></param>
	/// <param name="EnableFlag"></param>
	/// <param name="writeMask"></param>
	/// <param name="Func"></param>
	static void SettingDepth(
		D3D12_DEPTH_STENCIL_DESC &despthStencilDesc,
		bool EnableFlag,
		D3D12_DEPTH_WRITE_MASK writeMask,
		D3D12_COMPARISON_FUNC Func
	);

	static void CreatePSO(SPSO &pso);
	static void Create2dSpritePSOs(SPSO &pso);
	static void Create3dSpritePSOs(SPSO& pso);
	static void Create3dParticlePSOs(SPSO& pso);
	static void CreatePostEffectPSOs(SPSO& pso);

	static SPSOProperty CreateShape(ComPtr<ID3D12Device>device,Commands command,SShaderMode shader);
	static SPSOProperty CreateLine(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreateSprite3dNone(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);

	static SPSOProperty CreatePBR(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreatePhong(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreatePhongNormalModel(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreateSubsurfaceModel(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);

	static SPSOProperty CreateSprite2dNone(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreateSprite2dAdd(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreateSprite2dSubtract(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreateSprite2dMultiply(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreateSprite2dScreen(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);

	static SPSOProperty CreateParticle3dNone(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreateParticle3dAdd(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);

	static SPSOProperty CreatePostEffectTest(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreateShadow(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);

	static void DefferrdShading(SPSO &pso);

	SPSO pso = {};

};

