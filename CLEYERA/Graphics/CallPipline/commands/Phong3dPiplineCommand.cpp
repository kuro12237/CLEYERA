#include "Phong3dPiplineCommand.h"

void Phong3dPipline::Exec(const SModelData& modelData)
{
	ComPtr<ID3D12GraphicsCommandList>list = DirectXCommon::GetInstance()->GetCommands().m_pList;
	SPSOProperty PSO = GraphicsPipelineManager::GetInstance()->GetPso().PhongNormal_Model;
	list->SetGraphicsRootSignature(PSO.rootSignature.Get());
	list->SetPipelineState(PSO.GraphicsPipelineState.Get());
	DescriptorManager::rootParamerterCommand(7, modelData.normalTexHandle);

}
