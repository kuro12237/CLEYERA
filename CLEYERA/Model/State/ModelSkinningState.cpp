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

	influence_ = make_unique<BufferResource<VertexInfluence>>();
	influence_->CreateResource(sizeof(VertexInfluence) * state->GetModelData().vertices.size());
	//VertexInfluence* mappedInfuence = nullptr;
	influence_->CreateIndexBufferView();

}

void ModelSkinningState::CallPipelinexVertex(Model* state)
{
	state;
}

void ModelSkinningState::Draw(Model* state, const CameraData& viewprojection, uint32_t instancingNum)
{
	state, viewprojection, instancingNum;
}
