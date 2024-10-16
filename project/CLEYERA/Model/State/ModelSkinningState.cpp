#include "ModelSkinningState.h"

using namespace Engine::Base::DX;

using namespace Engine::Base::Win;
using namespace Engine::Objects;

using namespace Engine::Buffer;


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

	if (state->GetModelData().fileFormat == "GLTF")
	{
		D3D12_VERTEX_BUFFER_VIEW vbvs[2]{
			vertex_->GetBufferView(),
			state->GetInfluence()->GetBufferView()
		};
		commands.m_pList->IASetVertexBuffers(0, 2, vbvs);
	}
	index_->CommandIndexBufferViewCall();

	commands.m_pList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	commands.m_pList->DrawIndexedInstanced(UINT(state->GetModelData().indecs.size()), instancingNum, 0, 0, 0);
}
