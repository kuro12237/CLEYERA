#pragma once
#include"DirectXCommon.h"
#include"BufferResources.h"
#include"CreateResource.h"
#include"CameraData.h"
#include"IGameInstancing3dObject.h"
#include"ModelManager.h"
#include"Game3dObject.h"

class GameInstancing3dObject
{
public:
	GameInstancing3dObject() {};
	~GameInstancing3dObject() {};

	void Create(const uint32_t& kNum, const string& name);

	void Transfar();

	void Draw(const CameraData& camera);

	void SetModel(const uint32_t& index);

	void PushVector(shared_ptr<IGameInstancing3dObject> obj,uint32_t index);

private:
	bool CommpandPipeline(SPSOProperty& PSO);

	Model* model_ = nullptr;;

	uint32_t instancingNum_ = 1;
	string name_ = {};

	uint32_t srvHandle_ = 0;

	uint32_t modelHandle_ = 0;
	uint32_t prevModelIndex_ = 0;

	uint32_t texHandle_ = 0;
	uint32_t normalTexHandle_ = 0;
	uint32_t baseTexHandle_ = 0;

	bool UseLight_ = false;

	uint32_t ModelShaderSelect_ = PHONG_NORMAL_MODEL;

	vector<shared_ptr<IGameInstancing3dObject>>params_{};

	unique_ptr<BufferResource<TransformationMatrix>>instancing_=nullptr;
	vector<TransformationMatrix> instancingData_;

	unique_ptr<BufferResource<Material>>material_=nullptr;
	Material materialData_;
};