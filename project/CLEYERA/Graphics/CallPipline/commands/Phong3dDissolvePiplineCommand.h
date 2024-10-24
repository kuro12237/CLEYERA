#pragma once
#include"Graphics/CallPipline/IPipelineCommand.h"
#include"GraphicsPipelineManager.h"
#include"Graphics/DescripterManager/DescriptorManager.h"
#include"Utility/Noise/NoiseTexture.h"

/// <summary>
/// PhongDissolveŒÄ‚Ño‚µƒNƒ‰ƒX
/// </summary>
class Phong3dDissolvePipline :public IPipelineCommand
{
public:
	Phong3dDissolvePipline() {};
	~Phong3dDissolvePipline() {};

	void Exec(const SModelData& modelData)override;

private:

};