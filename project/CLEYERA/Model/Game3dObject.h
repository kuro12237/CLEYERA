#pragma once
#include"ModelManager.h"
#include"Light/DirectionLIght.h"
#include"Game3dObjectDesc.h"
#include"Graphics/PipelineManager/GraphicsPipelineManager.h"
#include"Animation/AnimationManager.h"

#include"Graphics/CallPipline/PipelineHandler.h"

class Game3dObject
{
public:
	Game3dObject() {};
	~Game3dObject() {};

	void Create(unique_ptr<IPipelineCommand> piplineSelect = nullptr);

	void SetModel(uint32_t index);

	void ChangePipline(unique_ptr<IPipelineCommand> piplineSelect);

	void Draw(WorldTransform worldTransform);

	void CreateSkinningParameter();

	void SkeletonUpdate(string fileName, float t);
	void SkinningUpdate();

	void SetObjectName(const string& name) { name_ = name; }

#pragma region Set

	void SetDesc(const Game3dObjectDesc& desc) { game3dObjectDesc_ = desc; }

	void SetName(string name) { name_ = name; }

#pragma endregion

#pragma region Get

	SAnimation::Skeleton &GetSkeleton() { return skeleton_; }
	bool GetSkinningFlag() { return skinningFlag_; }
	Game3dObjectDesc& GetDesc() { return game3dObjectDesc_; }

#pragma endregion


private:

	string name_;

	Model* model_ = nullptr;
	SModelData modelData_ = {};
	uint32_t prevModelIndex_ = 0;

	unique_ptr<PipelineHandler>piplineHandler_ = nullptr;

	unique_ptr<BufferResource<Material>>MaterialBuffer_ = nullptr;
	Material material_ = {};

	Material MaterialConverter();
	unique_ptr<BufferResource<SkinCluster>>cSkinCluster_ = nullptr;

#pragma region Skinning
	bool skinningFlag_ = false;
	SAnimation::Skeleton skeleton_;
	std::vector<Math::Matrix::Matrix4x4>inverseBindMatrices;
	unique_ptr<BufferResource<WellForGPU>>palette_ = nullptr;
	vector<WellForGPU>paletteParam_;
	//unique_ptr<BufferResource<>>
#pragma endregion

	Game3dObjectDesc game3dObjectDesc_{};

};