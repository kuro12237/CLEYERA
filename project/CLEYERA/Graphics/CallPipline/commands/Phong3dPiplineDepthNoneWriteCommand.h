#pragma once
#include"Graphics/CallPipline/IPipelineCommand.h"
#include"GraphicsPipelineManager.h"
#include"Graphics/DescripterManager/DescriptorManager.h"

class Phong3dSkinningPiplineDepthNoneWriteCommand :public IPipelineCommand
{
public:
	Phong3dSkinningPiplineDepthNoneWriteCommand() {};
	~Phong3dSkinningPiplineDepthNoneWriteCommand() {};

	void Exec(const SModelData& modelData)override;

private:

};