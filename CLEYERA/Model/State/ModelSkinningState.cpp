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
	//influenceの作成
	influence_ = make_unique<BufferResource<VertexInfluence>>();
	influence_->CreateResource(uint32_t(sizeof(VertexInfluence) * state->GetModelData().vertices.size()));
	influence_->CreateIndexBufferView();
	
	influence_->Map();
	vector<VertexInfluence> mappedInfuence;
	mappedInfuence.resize(state->GetModelData().vertices.size());

	SAnimation::Skeleton skeleton = state->GetModelData().node.skeleton;
	for (const auto& jointWeight : state->GetModelData().skinClusterData) {
		auto it = skeleton.jointMap.find(jointWeight.first);
		if (it == skeleton.jointMap.end()) {
			continue;
		}
		for (const auto& vertexWeight : jointWeight.second.vertexWeights) {
			auto& currentInfluence = mappedInfuence[vertexWeight.vertexIndex];
			// 空いているところに入れる
			for (uint32_t index = 0; index < kNumMaxInfluence; ++index) {
				// weight == 0 が空いている状態 その場所に代入
				if (currentInfluence.weights[index] == 0.0f) {
					currentInfluence.weights[index] = vertexWeight.weight;
					currentInfluence.jointIndicess[index] = (*it).second;
					break;
				}
			}
		}
	}
	influence_->Setbuffer(mappedInfuence);
}

void ModelSkinningState::CallPipelinexVertex(Model* state)
{
	state;
}

void ModelSkinningState::Draw(Model* state, const CameraData& viewprojection, uint32_t instancingNum)
{
	state, viewprojection, instancingNum;
}
