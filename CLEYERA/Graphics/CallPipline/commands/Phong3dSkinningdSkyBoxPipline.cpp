#include "Phong3dSkinningdSkyBoxPipline.h"

void Phong3dSkinningSkyBoxPipline::Exec(const SModelData& modelData)
{
	modelData;
	ComPtr<ID3D12GraphicsCommandList>list = DirectXCommon::GetInstance()->GetCommands().m_pList;
	SPSOProperty PSO = GraphicsPipelineManager::GetInstance()->GetPso().phongSkinningModel_SkyBox;
	list->SetGraphicsRootSignature(PSO.rootSignature.Get());
	list->SetPipelineState(PSO.GraphicsPipelineState.Get());
	SkyBox::GetInstance()->CommandCall(9);
}
