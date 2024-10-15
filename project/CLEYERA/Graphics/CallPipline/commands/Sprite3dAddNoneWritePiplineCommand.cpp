#include "Sprite3dAddNoneWritePiplineCommand.h"

using namespace Engine::Base::DX;

using namespace Engine::Base::Win;

void Sprite3dAddNoneWritePiplineCommand::Exec(const SModelData& modelData)
{
	modelData;
	ComPtr<ID3D12GraphicsCommandList>list = DirectXCommon::GetInstance()->GetCommands().m_pList;
	SPSOProperty PSO = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::SPRITE_3d, "AddNoneWriteDepth");
	list->SetGraphicsRootSignature(PSO.rootSignature.Get());
	list->SetPipelineState(PSO.GraphicsPipelineState.Get());
}
