#pragma once
#include"StructGraphicsPipline.h"
#include"CreateGraphicsPiplineFanc.h"
#include"ShaderManager.h"

class CreateGpuParticle
{
public:
	
	static SPSOProperty CreateGpuParticle_Init(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);

	static SPSOProperty CreateGpuParticle_DebugDraw(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);

private:

};
