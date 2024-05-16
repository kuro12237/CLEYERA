#pragma once
#include"CreateGraphicsPiplineFanc.h"
#include"ShaderManager.h"

class SkinningCreatePipline
{
public:

	static SPSOProperty CreateSkinningPhongModel(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);

private:

	static void CreateSkinningPhongRootSignature(ComPtr<ID3D12Device> device,SPSOProperty& pso);
	static D3D12_INPUT_LAYOUT_DESC CreateSkinningPhongInputDesc();
};