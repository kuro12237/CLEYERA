#include "ModelSkinningState.h"

ModelSkinningState::~ModelSkinningState()
{
}

void ModelSkinningState::Initialize(Model* state)
{
	//頂点作成
	vertex_ = make_unique<BufferResource<VertexData>>();
	vertex_->CreateResource(uint32_t(state->GetModelData().vertices.size()));
	vertex_->CreateVertexBufferView();
	//IndexBufferの作成
	index_ = make_unique<BufferResource<uint32_t>>();
	index_->CreateResource(uint32_t(state->GetModelData().indecs.size()));
	index_->CreateIndexBufferView();

}

void ModelSkinningState::Draw(Model* state,uint32_t instancingNum)
{
	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	//vertex
	vertex_->Map();
	vertex_->Setbuffer(state->GetModelData().vertices);
	vertex_->UnMap();
	//Index
	index_->Map();
	index_->Setbuffer(state->GetModelData().indecs);
	index_->UnMap();


	index_->CommandIndexBufferViewCall();

	commands.m_pList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	commands.m_pList->DrawIndexedInstanced(UINT(state->GetModelData().indecs.size()), instancingNum, 0, 0, 0);
}
