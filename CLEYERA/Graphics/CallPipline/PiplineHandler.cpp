#include "PipelineHandler.h"

void PipelineHandler::UsePipeline(unique_ptr<IPipelineCommand> &usePipline)
{
	command_ = move(usePipline);
}

void PipelineHandler::Call(const SModelData& modelData)
{
	command_->Exec(modelData);
}
