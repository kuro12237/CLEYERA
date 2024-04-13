#include "ModelObjState.h"

ModelObjState::~ModelObjState()
{
	
}

void ModelObjState::Initialize(Model* state)
{
	vertex_ = make_unique<BufferResource<VertexData>>();
	vertex_->CreateResource(uint32_t(state->GetModelData().vertices.size()));
	vertex_->CreateVertexBufferView();
	//IndexBufferの作成
	index_ = make_unique<BufferResource<uint32_t>>();
	index_->CreateResource(uint32_t(state->GetModelData().indecs.size()));
	index_->CreateIndexBufferView();
}

void ModelObjState::CallPipelinexVertex(Model* state)
{
	state;
	vertex_->CommandVertexBufferViewCall();
	vertex_->CommandPrimitiveTopologyCall();
}

void ModelObjState::Draw(Model* state, const CameraData& viewprojection)
{
	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	vertex_->Map();
	vertex_->Setbuffer(state->GetModelData().vertices);
	//IndexBufferのMap
	index_->Map();
	index_->Setbuffer(state->GetModelData().indecs);
	index_->CommandIndexBufferViewCall();
	
	//Light
	if (state->GetUseLight())
	{
		viewprojection.buffer_->CommandCall(3);

		DescriptorManager::rootParamerterCommand(4, LightingManager::dsvHandle());
		commands.m_pList->SetGraphicsRootConstantBufferView(5, LightingManager::GetBuffer()->GetGPUVirtualAddress());
	}

	commands.m_pList->DrawIndexedInstanced(UINT(state->GetModelData().indecs.size()), 1, 0, 0, 0);
	
}