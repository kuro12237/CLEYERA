#pragma once
#include"Graphics/CallPipline/IPipelineCommand.h"
#include"GraphicsPipelineManager.h"
#include"Graphics/DescripterManager/DescriptorManager.h"
#include"Utility/Noise/NoiseTexture.h"

/// <summary>
/// PhongDissolve呼び出しクラス
/// </summary>
class PBRPiplineCommand :public IPipelineCommand
{
public:

	PBRPiplineCommand() {};
	~PBRPiplineCommand() {};

	void Exec(const SModelData& modelData)override;

private:

};