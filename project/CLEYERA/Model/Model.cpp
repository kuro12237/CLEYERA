#include "Model.h"

using namespace Math::Vector;
using namespace Engine::Objects;
using namespace Engine::Buffer;


Model::~Model(){}

void Model::CreateModel(unique_ptr<IModelState> state)
{
	state_=move(state);
	state_->Initialize(this);
}

void Model::Draw(uint32_t instancingNum)
{
	if (state_ == nullptr)
	{
		LogManager::Log("None SetModel\n");
		assert(0);
	}
	
	state_->Draw(this,instancingNum);
}

void Model::SetStateType(SModelData modelData, ModelFormatType type)
{
	modelData_ = modelData;
	if (type == OBJECT && !modelData.skinningFlag_)
	{
		state_ = make_unique<ModelObjState>();
		state_->Initialize(this);
	}
	else if (type == GLTF && modelData.skinningFlag_)
	{
		state_ = make_unique<ModelSkinningState>();
		state_->Initialize(this);
		{
			//合計頂点数のバッファ作成
			vertexNum_ = make_unique<BufferResource<uint32_t>>();
			vertexNum_->CreateResource(1);
			vertexNum_->Map();
			vertexCountNum_ = uint32_t(modelData_.vertices.size());
			vertexNum_->Setbuffer(vertexCountNum_);
			vertexNum_->UnMap();

			//influence作成
			influence_ = make_unique<BufferResource<VertexInfluence>>();
			influence_->CreateResource(uint32_t(modelData_.vertices.size()));
			influence_->CreateVertexBufferView();
			influence_->Map();
			//sizeを確保
			mappedInfluence.resize(modelData_.vertices.size());
			modelData_.inverseBindMatrices.resize(modelData_.skeleton.joints.size());
			std::generate(modelData_.inverseBindMatrices.begin(), modelData_.inverseBindMatrices.end(), Math::Matrix::Identity);

			for (const auto& jointWeight : modelData_.skinClusterData) {
				auto it = modelData_.skeleton.jointMap.find(jointWeight.first);
				if (it == modelData_.skeleton.jointMap.end()) {
					continue;
				}
				// (*it).secondにはjointのindexが入っているので、該当のIndexのinverseBindPoseMatrixを代入
				modelData_.inverseBindMatrices[(*it).second] = jointWeight.second.inverseBindPoseMatrix;
				for (const auto& vertexWeight : jointWeight.second.vertexWeights) {
					auto& currentInfluence = mappedInfluence[vertexWeight.vertexIndex];
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
			influence_->Setbuffer(mappedInfluence);
			influence_->UnMap();
		}
	}
}