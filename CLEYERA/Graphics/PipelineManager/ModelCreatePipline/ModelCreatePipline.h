#pragma once
#include"StructGraphicsPipline.h"
#include"CreateGraphicsPiplineFanc.h"
#include"ShaderManager.h"

class ModelCreatePipline
{
public:
	
	static void CreatePiplines();

	static SPSOProperty CreateSpriteModel();

	static SPSOProperty CreatePhongModel();

	static SPSOProperty CreatePhongNormalModel();

	static SPSOProperty CreateColorModel(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);

	static SPSOProperty CreateNormalModel(ComPtr<ID3D12Device>device, Commands, SShaderMode shader);


private:

};
