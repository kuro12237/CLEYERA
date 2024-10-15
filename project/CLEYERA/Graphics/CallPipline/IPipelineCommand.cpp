#include "IPipelineCommand.h"

using namespace Engine::Base::DX;

using namespace Engine::Base::Win;

void IPipelineCommand::CallCommand()
{
	
	ComPtr<ID3D12GraphicsCommandList>list = DirectXCommon::GetInstance()->GetCommands().m_pList;
	list->SetGraphicsRootSignature(pso_.rootSignature.Get());
	list->SetPipelineState(pso_.GraphicsPipelineState.Get());

}
