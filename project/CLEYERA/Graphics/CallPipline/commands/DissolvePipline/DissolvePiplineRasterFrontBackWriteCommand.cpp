#include "DissolvePiplineRasterFrontBackWriteCommand.h"

void Phong3dDissolvePiplineRasterFrontBackWriteCommand::Exec(const SModelData& modelData)
{
	modelData;
	SPSOProperty PSO = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::PHONG, "Dissolve_FrontBackWrite");
	SetPso(PSO);
	CallCommand();
	DescriptorManager::rootParamerterCommand(8, NoiseTexture::GetInstance()->GetIndex());

	DescriptorManager::rootParamerterCommand(7, modelData.normalTexHandle);
}
