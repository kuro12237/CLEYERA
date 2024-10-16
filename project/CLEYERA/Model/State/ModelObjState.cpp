#include "ModelObjState.h"

using namespace Engine::Base::DX;

using namespace Engine::Base::Win;

using namespace Engine::Objects;

using namespace Engine::Buffer;


ModelObjState::~ModelObjState() {}

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

void ModelObjState::Draw(Model* state, uint32_t instancingNum)
{
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
	index_->CommandIndexBufferViewCall();

	commands.m_pList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	commands.m_pList->DrawIndexedInstanced(UINT(state->GetModelData().indecs.size()), instancingNum, 0, 0, 0);
}