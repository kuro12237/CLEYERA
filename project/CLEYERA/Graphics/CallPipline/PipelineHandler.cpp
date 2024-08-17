#include "PipelineHandler.h"

void PipelineHandler::UsePipeline(unique_ptr<IPipelineCommand> &usePipline)
{
	if (command_)
	{
		command_.release();
	}
	command_ = move(usePipline);
}


void PipelineHandler::Call(const SModelData& modelData)
{
	command_->Exec(modelData);
}
