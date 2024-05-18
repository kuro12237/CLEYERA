#include "Phong3dSkinningPipline.h"

void Phong3dSkinningPipline::Exec(const SModelData& modelData)
{
	SPSOProperty PSO = GraphicsPipelineManager::GetInstance()->GetPso().Phong_SkinningModel;
	SetPso(PSO);
	CallCommand();

	DescriptorManager::rootParamerterCommand(7, modelData.normalTexHandle);
}
