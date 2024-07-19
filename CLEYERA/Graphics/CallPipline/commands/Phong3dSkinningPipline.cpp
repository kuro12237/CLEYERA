#include "Phong3dSkinningPipline.h"

void Phong3dSkinningPipline::Exec(const SModelData& modelData)
{
	SPSOProperty PSO = GraphicsPipelineManager::GetInstance()->GetPso().PhongNormal_Model;
	SetPso(PSO);
	CallCommand();

	DescriptorManager::rootParamerterCommand(7, modelData.normalTexHandle);
}
