#include "Phong3dSkinningPipline.h"

void Phong3dSkinningPipline::Exec()
{
	SPSOProperty PSO = GraphicsPipelineManager::GetInstance()->GetPso().Phong_SkinningModel;
	SetPso(PSO);
	CallCommand();
}
