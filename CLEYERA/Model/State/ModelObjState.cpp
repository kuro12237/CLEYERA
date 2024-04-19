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

void ModelObjState::Draw(Model* state, const CameraData& viewprojection, uint32_t instancingNum)
{
	viewprojection;
	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	vertex_->Map();
	vertex_->Setbuffer(state->GetModelData().vertices);
	vertex_->UnMap();
	//IndexBufferのMap
	index_->Map();
	index_->Setbuffer(state->GetModelData().indecs);
	index_->UnMap();

	vertex_->CommandVertexBufferViewCall();

	index_->CommandIndexBufferViewCall();
	vertex_->CommandPrimitiveTopologyCall();

	commands.m_pList->DrawIndexedInstanced(UINT(state->GetModelData().indecs.size()), instancingNum, 0, 0, 0);
	
}