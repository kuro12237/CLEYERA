#include "PBRPiplineCommand.h"

void PBRPiplineCommand::Exec(const SModelData& modelData)
{
	modelData;
	SPSOProperty PSO = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::PBR, "None");
	SetPso(PSO);
	CallCommand();

	//DescriptorManager::rootParamerterCommand(7, modelData.normalTexHandle);
}
