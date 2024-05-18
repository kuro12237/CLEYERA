#pragma once
#include"Graphics/CallPipline/IPipelineCommand.h"
#include"GraphicsPipelineManager.h"

class Phong3dSkinningPipline :public IPipelineCommand
{
public:
	Phong3dSkinningPipline() {};
	~Phong3dSkinningPipline() {};

	void Exec()override;

private:

};