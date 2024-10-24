#pragma once
#include"StructGraphicsPipline.h"
#include"CreateGraphicsPiplineFanc.h"
#include"ShaderManager.h"


/// <summary>
/// スカイボックスパイプライン作製関数
/// </summary>
class ModelCreatePipline
{
public:

	static SPSOProperty CreateSkyBoxModel(ComPtr<ID3D12Device>device, Engine::Base::DX::Commands commands, SShaderMode shader);

private:

};
