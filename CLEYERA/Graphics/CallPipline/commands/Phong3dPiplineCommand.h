#pragma once
#include"Graphics/CallPipline/IPipelineCommand.h"
#include"GraphicsPipelineManager.h"

class Phong3dPipline :public IPipelineCommand
{
public:
	Phong3dPipline() {};
	~Phong3dPipline() {};

	void Exec()override;

private:

};