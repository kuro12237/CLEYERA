#pragma once
#include"Pch.h"
#include"ModelObjData.h"
#include"Graphics/TextureManager/TextureManager.h"
#include"Quaternion/QuaternionTransform.h"
#include"Animation/SAnimation.h"
#include"Utility/CameraManager/CameraManager.h"

class ModelManager
{
public:

	static ModelManager* GetInstance();

	static void Initialize();

	static void Finalize();

	/// <summary>
	/// NormalMapを読み込む際LLOadObjFile関数の前にこれを呼び出す
	/// </summary>
	static void ModelLoadNormalMap();

	static void ModelUseSubsurface();

	static void UnUseFilePath();

	/// <summary>
	/// objファイルの読み込み
	/// </summary>
	/// <param name="Modelfileの中のファイル名"></param>
	/// <returns></returns>
	static uint32_t LoadObjectFile(string directoryPath);

	static uint32_t LoadGltfFile(string directoryPath,bool skinningFlag = false);

	/// <summary>
	/// ハンドルのobjデータのGet
	/// </summary>
	static SModelData GetObjData(uint32_t index);

	static SModelData GetModelData(const string filePath);

	static Model* GetModel(uint32_t index);

	static Model* GetModel(const string filePath);

	static uint32_t GetIndex(const string name) { return ModelManager::GetInstance()->objModelDatas_[name]->GetIndex(); }

	static void SkeletonUpdate(SAnimation::Skeleton& skeleton);

	static void SkinClusterUpdate(SkinCluster& skinCluster, SAnimation::Skeleton& skeleton);

	static SAnimation::Skeleton CreateSkeleton(const NodeData& rootNode);

	static SkinCluster CreateSkinCluster(const SAnimation::Skeleton& skeleton, const SModelData& modelData);

private:

	static bool ChackLoadObj(string filePath);

	static NodeData ReadNodeData(aiNode*node);

	static int32_t CreateJoint(const NodeData& node, const std::optional<int32_t>& parent, std::vector<SAnimation::Joint>& joints);

	static void CreateVerteces(SModelData& data, aiMesh* mesh);
	static void CreateBorn(SModelData& data, aiMesh* mesh);

	map<string,unique_ptr<ModelObjData>>objModelDatas_;
	uint32_t objHandle_ = 0;

	bool isLoadNormalMap_ = false;
	bool isUsesubsurface_ = false;

	bool isUseFilePath_ = true;

#pragma region 
	//Singleton
	ModelManager() = default;
	~ModelManager() = default;
	ModelManager(const ModelManager&) = delete;
	const ModelManager& operator=(const ModelManager&) = delete;
#pragma endregion 

};
