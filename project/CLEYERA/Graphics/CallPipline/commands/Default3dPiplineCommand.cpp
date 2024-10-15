#include "Default3dPiplineCommand.h"

using namespace Engine::Base::DX;

using namespace Engine::Base::Win;

void Default3dPipline::Exec(const SModelData& modelData)
{
	modelData;
	ComPtr<ID3D12GraphicsCommandList>list = DirectXCommon::GetInstance()->GetCommands().m_pList;
	SPSOProperty PSO = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::NONE_3d, "None");
    list->SetGraphicsRootSignature(PSO.rootSignature.Get());
    list->SetPipelineState(PSO.GraphicsPipelineState.Get());
}
