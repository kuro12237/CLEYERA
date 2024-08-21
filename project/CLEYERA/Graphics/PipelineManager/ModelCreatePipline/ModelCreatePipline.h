#pragma once
#include"StructGraphicsPipline.h"
#include"CreateGraphicsPiplineFanc.h"
#include"ShaderManager.h"

class ModelCreatePipline
{
public:

	static SPSOProperty CreateSkyBoxModel(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);

private:

};
