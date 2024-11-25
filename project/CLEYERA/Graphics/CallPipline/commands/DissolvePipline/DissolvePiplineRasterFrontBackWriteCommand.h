#pragma once
#include"Graphics/CallPipline/IPipelineCommand.h"
#include"GraphicsPipelineManager.h"
#include"Graphics/DescripterManager/DescriptorManager.h"
#include"Utility/Noise/NoiseTexture.h"

/// <summary>
/// PhongDissolve表裏書くパイプライン呼び出しクラス
/// </summary>
class Phong3dDissolvePiplineRasterFrontBackWriteCommand :public IPipelineCommand
{
public:
	Phong3dDissolvePiplineRasterFrontBackWriteCommand() {};
	~Phong3dDissolvePiplineRasterFrontBackWriteCommand() {};

	void Exec(const SModelData& modelData)override;

private:

};