#pragma once
#include"Graphics/CallPipline/IPipelineCommand.h"
#include"GraphicsPipelineManager.h"
#include"Graphics/DescripterManager/DescriptorManager.h"

class Phong3dSkinningPipline :public IPipelineCommand
{
public:
	Phong3dSkinningPipline() {};
	~Phong3dSkinningPipline() {};

	void Exec(const SModelData& modelData)override;

private:

};