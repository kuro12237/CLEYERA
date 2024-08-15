#pragma once
#include"Graphics/CallPipline/IPipelineCommand.h"
#include"GraphicsPipelineManager.h"
#include"Graphics/DescripterManager/DescriptorManager.h"

class Phong3dPipline :public IPipelineCommand
{
public:
	Phong3dPipline() {};
	~Phong3dPipline() {};

	void Exec(const SModelData& modelData)override;

private:

};