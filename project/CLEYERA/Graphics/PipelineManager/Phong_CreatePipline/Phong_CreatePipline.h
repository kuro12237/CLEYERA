#pragma once
#include"Graphics/PipelineManager/StructGraphicsPipline.h"
#include"CreateGraphicsPiplineFanc.h"
#include"ShaderManager.h"

/// <summary>
/// Phongパイプライン作製関数
/// </summary>
class Phong_CreatePipline
{
public:

	static Phong_CreatePipline* GetInstance();

	void Initialize();

	SPSOProperty CreatePhongNormalModel(SShaderMode shader);
	SPSOProperty CreateDissolveNormalModel(SShaderMode shader);
	SPSOProperty CreateSubsurfaceModel(SShaderMode shader);

	SPSOProperty CreateInstancingModel(SShaderMode shader);
	SPSOProperty CreateSkinningModel(SShaderMode shader);

private:
	ComPtr<ID3D12Device>device = nullptr;
	ComPtr<ID3D12GraphicsCommandList>commandList_ = nullptr;
};
