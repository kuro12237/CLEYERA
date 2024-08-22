#pragma once
#include"Graphics/CallPipline/IPipelineCommand.h"
#include"GraphicsPipelineManager.h"

class  Sprite3dAddNoneWritePiplineCommand :public IPipelineCommand
{
public:
	Sprite3dAddNoneWritePiplineCommand() {};
	~Sprite3dAddNoneWritePiplineCommand() {};

	void Exec(const SModelData& modelData)override;

private:

};