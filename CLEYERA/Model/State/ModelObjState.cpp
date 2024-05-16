#include "ModelObjState.h"

ModelObjState::~ModelObjState()
{
	
}

void ModelObjState::Initialize(Model* state)
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

	if (state->GetModelData().fileFormat == "OBJ")
	{
		vertex_->CommandVertexBufferViewCall();
	}
	if (state->GetModelData().fileFormat == "GLTF")
	{
		//skinningAnimationの際通る
		D3D12_VERTEX_BUFFER_VIEW vbvs[2]{
			vertex_->GetBufferView(),
			state->GetModelData().skinCluster.influenceBufferView
		};
		commands.m_pList->IASetVertexBuffers(0, 2, vbvs);
		uint32_t srvHandle = state->GetModelData().skinCluster.srvIndex;
		DescriptorManager::rootParamerterCommand(7, srvHandle);
	}

	vertex_->CommandVertexBufferViewCall();
	index_->CommandIndexBufferViewCall();
	vertex_->CommandPrimitiveTopologyCall();

	commands.m_pList->DrawIndexedInstanced(UINT(state->GetModelData().indecs.size()), instancingNum, 0, 0, 0);

}