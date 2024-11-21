#pragma once
#include"Pch.h"
#include"ModelObjData.h"
#include"Graphics/TextureManager/TextureManager.h"
#include"Quaternion/QuaternionTransform.h"
#include"Animation/SAnimation.h"
#include"Utility/CameraManager/CameraManager.h"

namespace Engine::Manager
{
	/// <summary>
	/// モデル読み込み管理クラス
	/// </summary>
	class ModelManager
	{
	public:

		static ModelManager* GetInstance();

		/// <summary>
		/// 初期化
		/// </summary>
		static void Initialize();

		/// <summary>
		/// 終わり
		/// </summary>
		static void Finalize();

		/// <summary>
		/// NormalMapを読み込む際LLOadObjFile関数の前にこれを呼び出す
		/// </summary>
		static void ModelLoadNormalMap();

		/// <summary>
		/// サブサーフェースを使う
		/// </summary>
		static void ModelUseSubsurface();

		/// <summary>
		/// ファイルパスの省略を使わない
		/// </summary>
		static void UnUseFilePath();

		/// <summary>
		/// objファイルの読み込み
		/// </summary>
		/// <param name="Modelfileの中のファイル名"></param>
		/// <returns></returns>
		static uint32_t LoadObjectFile(string directoryPath);

		/// <summary>
		/// gltfの読み込み
		/// </summary>
		/// <param name="ファイルパス"></param>
		/// <param name="skinningFlagするか"></param>
		/// <returns></returns>
		static uint32_t LoadGltfFile(string directoryPath, bool skinningFlag = false);

#pragma region Get
		static SModelData GetObjData(uint32_t index);

		static SModelData GetModelData(const string filePath);

		static Engine::Objects::Model* GetModel(uint32_t index);

		static Engine::Objects::Model* GetModel(const string filePath);

		static uint32_t GetIndex(const string name) { return ModelManager::GetInstance()->objModelDatas_[name]->GetIndex(); }

#pragma endregion
		/// <summary>
		/// 骨更新
		/// </summary>
		/// <param name="skeleton"></param>
		static void SkeletonUpdate(SAnimation::Skeleton& skeleton);

		/// <summary>
		/// 骨作製
		/// </summary>
		/// <param name="rootNode"></param>
		/// <returns></returns>
		static SAnimation::Skeleton CreateSkeleton(const NodeData& rootNode);

		/// <summary>
		/// バッファ作製
		/// </summary>
		/// <param name="skeleton"></param>
		/// <param name="modelData"></param>
		/// <returns></returns>
		static SkinCluster CreateSkinCluster(const SAnimation::Skeleton& skeleton, const SModelData& modelData);

	private:

		/// <summary>
		/// 読み込んだことがあるかをチェック
		/// </summary>
		/// <param name="filePath"></param>
		/// <returns></returns>
		static bool ChackLoadObj(string filePath);


		/// <summary>
		/// 再帰でノードを読み込む
		/// </summary>
		/// <param name="node"></param>
		/// <returns></returns>
		static NodeData ReadNodeData(aiNode* node);

		/// <summary>
		/// ジョイント作製
		/// </summary>
		/// <param name="node"></param>
		/// <param name="parent"></param>
		/// <param name="joints"></param>
		/// <returns></returns>
		static int32_t CreateJoint(const NodeData& node, const std::optional<int32_t>& parent, std::vector<SAnimation::Joint>& joints);

		/// <summary>
		/// 頂点作成
		/// </summary>
		/// <param name="data"></param>
		/// <param name="mesh"></param>
		static void CreateVerteces(SModelData& data, aiMesh* mesh);

		/// <summary>
		/// 骨作製
		/// </summary>
		/// <param name="data"></param>
		/// <param name="mesh"></param>
		static void CreateBorn(SModelData& data, aiMesh* mesh);

		map<string, unique_ptr<ModelObjData>>objModelDatas_;
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
}
