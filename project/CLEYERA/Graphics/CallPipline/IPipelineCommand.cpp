#include "IPipelineCommand.h"

void IPipelineCommand::CallCommand()
{
	
	ComPtr<ID3D12GraphicsCommandList>list = DirectXCommon::GetInstance()->GetCommands().m_pList;
	list->SetGraphicsRootSignature(pso_.rootSignature.Get());
	list->SetPipelineState(pso_.GraphicsPipelineState.Get());

}
