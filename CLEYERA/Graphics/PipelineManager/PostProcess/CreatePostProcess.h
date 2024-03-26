#pragma once
#include"StructGraphicsPipline.h"
#include"CreateGraphicsPiplineFanc.h"
#include"ShaderManager.h"

class CreatePostProcess
{
public:
	CreatePostProcess() {};
	~CreatePostProcess() {};

	static SPSOProperty DefferdShading(ComPtr<ID3D12Device>device, Commands, SShaderMode shader);

private:

};