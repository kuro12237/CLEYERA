#pragma once
#include"Graphics/PipelineManager/StructGraphicsPipline.h"
#include"CreateGraphicsPiplineFanc.h"
#include"ShaderManager.h"

class Sprite_2d_CreatePipline
{
public:

	static Sprite_2d_CreatePipline* GetInstance();

	void Initialize();

	SPSOProperty CreateNone(SShaderMode shader);
	SPSOProperty CreateAdd(SShaderMode shader);
	SPSOProperty CreateSubtract(SShaderMode shader);
	SPSOProperty CreateMultiply(SShaderMode shader);
	SPSOProperty CreateScreen(SShaderMode shader);

	SPSOProperty CreateDissolveNone(SShaderMode shader);
	SPSOProperty CreatePerlinNoise(SShaderMode shader);

private:
	ComPtr<ID3D12Device>device = nullptr;
	ComPtr<ID3D12GraphicsCommandList>commandList_ = nullptr;
};

