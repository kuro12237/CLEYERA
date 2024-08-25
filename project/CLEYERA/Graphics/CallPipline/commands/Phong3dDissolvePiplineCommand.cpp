#include "Phong3dDissolvePiplineCommand.h"

void Phong3dDissolvePipline::Exec(const SModelData& modelData)
{
	modelData;
	SPSOProperty PSO = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::PHONG, "Dissolve");
	SetPso(PSO);
	CallCommand();
	DescriptorManager::rootParamerterCommand(8,NoiseTexture::GetInstance()->GetIndex());

	DescriptorManager::rootParamerterCommand(7, modelData.normalTexHandle);
}
