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

	/// <summary>
	/// 名前で指定数作製
	/// </summary>
	/// <param name="kNum"></param>
	/// <param name="name"></param>
	void Create(const uint32_t& kNum, const string& name);

	/// <summary>
	/// GPUに転送
	/// </summary>
	void Transfar();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// モデルのハンドル設定
	/// </summary>
	/// <param name="index"></param>
	void SetModel(const uint32_t& index);

	/// <summary>
	/// 物を設定
	/// </summary>
	/// <param name="obj"></param>
	/// <param name="index"></param>
	void PushVector(shared_ptr<IGameInstancing3dObject> obj,uint32_t index);


private:

	bool CommpandPipeline(SPSOProperty& PSO);

	Engine::Objects::Model* model_ = nullptr;;

	uint32_t instancingNum_ = 1;
	string name_ = {};

	
	uint32_t modelHandle_ = 0;
	uint32_t prevModelIndex_ = 0;

	uint32_t texHandle_ = 0;
	uint32_t normalTexHandle_ = 0;
	uint32_t baseTexHandle_ = 0;

	bool UseLight_ = false;


	vector<shared_ptr<IGameInstancing3dObject>>params_{};

	unique_ptr<Engine::Buffer::BufferResource<TransformationMatrix>>instancing_=nullptr;
	vector<TransformationMatrix> instancingData_;

	unique_ptr<Engine::Buffer::BufferResource<Material>>material_=nullptr;
	Material materialData_;
};