#pragma once
#include"Pch.h"
#include"IPipelineCommand.h"
#include"Graphics/CallPipline/commands/Default3dPiplineCommand.h"
#include"commands/Phong3dPiplineCommand.h"
#include"commands/Phong3dSkinningPipline.h"

class PipelineHandler
{
public:
	PipelineHandler() {};
	~PipelineHandler() {};

	void UsePipeline(unique_ptr<IPipelineCommand> &usePipline);

	void Call(const SModelData &modelData);

private:

	unique_ptr<IPipelineCommand>command_ = nullptr;

};