#include "Phong3dPiplineCommand.h"

using namespace Engine::Base::DX;

using namespace Engine::Base::Win;

void Phong3dPipline::Exec(const SModelData& modelData)
{
	modelData;
	ComPtr<ID3D12GraphicsCommandList>list = DirectXCommon::GetInstance()->GetCommands().m_pList;
	SPSOProperty PSO = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::PHONG, "None");
	list->SetGraphicsRootSignature(PSO.rootSignature.Get());
	list->SetPipelineState(PSO.GraphicsPipelineState.Get());

	DescriptorManager::rootParamerterCommand(7, modelData.normalTexHandle);
}
