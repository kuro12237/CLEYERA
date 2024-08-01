#pragma once
#include"StructGraphicsPipline.h"
#include"CreateGraphicsPiplineFanc.h"
#include"ShaderManager.h"

class ModelCreatePipline
{
public:

	static SPSOProperty CreateSpriteModel();

	static SPSOProperty CreatePhongNormalModel();

	static SPSOProperty CreatePhongInstancingModel(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);

	static SPSOProperty CreateSkyBoxModel(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);

	static SPSOProperty CreateSkyBoxxPhongSkinnningModel(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);

private:

};
