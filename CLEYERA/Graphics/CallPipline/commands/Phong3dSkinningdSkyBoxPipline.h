#pragma once
#include"Graphics/CallPipline/IPipelineCommand.h"
#include"GraphicsPipelineManager.h"
#include"Graphics/DescripterManager/DescriptorManager.h"
#include"Utility/SkyBox/SkyBox.h"

class Phong3dSkinningSkyBoxPipline :public IPipelineCommand
{
public:
	Phong3dSkinningSkyBoxPipline() {};
	~Phong3dSkinningSkyBoxPipline() {};

	void Exec(const SModelData& modelData)override;

private:

};