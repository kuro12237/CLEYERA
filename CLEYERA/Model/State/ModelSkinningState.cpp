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

void ModelSkinningState::CallPipelinexVertex(Model* state)
{
	state;
	vertex_->CommandPrimitiveTopologyCall();
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

	if (state->GetModelData().fileFormat == "GLTF")
	{
		D3D12_VERTEX_BUFFER_VIEW vbvs[2]{
			vertex_->GetBufferView(),
			state->GetInfluence()->GetBufferView()
			//state->GetDesc().skinningAnimationDesc.skinCluster.influenceBufferView
		};
		commands.m_pList->IASetVertexBuffers(0, 2, vbvs);
		DescriptorManager::rootParamerterCommand(7, state->GetDesc().skinningAnimationDesc.skinCluster.srvIndex);
	}
	index_->CommandIndexBufferViewCall();
	vertex_->CommandPrimitiveTopologyCall();
	commands.m_pList->DrawIndexedInstanced(UINT(state->GetModelData().indecs.size()), instancingNum, 0, 0, 0);
}