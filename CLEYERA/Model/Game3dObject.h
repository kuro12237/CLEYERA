#pragma once
#include"ModelManager.h"
#include"Light/DirectionLIght.h"
#include"Game3dObjectDesc.h"
#include"Graphics/PipelineManager/GraphicsPipelineManager.h"
#include"Animation/AnimationManager.h"

class Game3dObject
{
public:
	Game3dObject() {};
	~Game3dObject() {};

	void Create();

	void SetModel(uint32_t index);

	void Draw(WorldTransform worldTransform, CameraData view);

	void CreateSkinningParameter();

	void SkeletonUpdate(string fileName, float t);

	void SkinningUpdate();

	void SetObjectName(const string& name) { name_ = name; }

#pragma region Set

	void SetDesc(const Game3dObjectDesc& desc) { game3dObjectDesc_ = &desc; }

	void SetName(string name) { name_ = name; }

	void SetTexHandle(uint32_t index) { texHandle_ = index; }
	void SetNormalTex(uint32_t tex) { normalTexHandle_ = tex; }
	void SetBaseTex(uint32_t tex) { baseTexHandle_ = tex; }

#pragma endregion

private:

	string name_;

	Model* model_ = nullptr;
	uint32_t prevModelIndex_ = 0;

	bool isIndexDraw = false;
	bool CommpandPipeline(SPSOProperty& PSO);

	unique_ptr<BufferResource<Material>>MaterialBuffer_ = nullptr;
	Material material_ = {};

	unique_ptr<BufferResource<SkinCluster>>cSkinCluster_ = nullptr;

#pragma region Skinning

	SAnimation::Skeleton skeleton_;

	std::vector<Math::Matrix::Matrix4x4>inverseBindMatrices;

	unique_ptr<BufferResource<WellForGPU>>palette_ = nullptr;
	vector<WellForGPU>paletteParam_;
#pragma endregion

	const Game3dObjectDesc* game3dObjectDesc_ = nullptr;

	uint32_t texHandle_ = 0;
	uint32_t normalTexHandle_ = 0;
	uint32_t baseTexHandle_ = 0;

	uint32_t ModelShaderSelect_ = 0;
};