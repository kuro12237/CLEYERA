#pragma once
#include"Graphics/CallPipline/IPipelineCommand.h"
#include"GraphicsPipelineManager.h"

class Default3dPipline:public IPipelineCommand
{
public:
	Default3dPipline() {};
	~Default3dPipline() {};

	void Exec()override;

private:

};