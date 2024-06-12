#pragma once
#include"CreateGraphicsPiplineFanc.h"
#include"ShaderManager.h"

class SkinningCreateComputePipline
{
public:

	static SPSOProperty CreateSkinningPipline(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);

private:

	static void CreateSkinningRootSignature(ComPtr<ID3D12Device> device, SPSOProperty& pso);


};

