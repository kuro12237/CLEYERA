#include "Phong3dPiplineDepthNoneWriteCommand.h"

void Phong3dSkinningPiplineDepthNoneWriteCommand::Exec(const SModelData& modelData)
{
	SPSOProperty PSO = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::PHONG, "Skinning_NoneDepthWrite");
	SetPso(PSO);
	CallCommand();

	DescriptorManager::rootParamerterCommand(7, modelData.normalTexHandle);
}
