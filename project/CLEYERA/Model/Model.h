#pragma once
#include"Pch.h"
#include"Graphics/TextureManager/TextureManager.h"

#include"ModelObjState.h"
#include"ModelSkinningState.h"

#include"WorldTransform.h"
#include"CameraData.h"
#include"Light/Light.h"
#include"Game3dObjectDesc.h"

enum ModelFormatType
{
	OBJECT,
	GLTF
};

namespace Engine::Objects {

	using namespace Engine::Buffer;

	class Model
	{
	public:
		~Model();

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="state"></param>
		void CreateModel(unique_ptr<IModelState> state);

		/// <summary>
		/// 表示
		/// </summary>
		/// <param name="instancingNum"></param>
		void Draw(uint32_t instancingNum);

		/// <summary>
		/// パラメータ構造体設定
		/// </summary>
		/// <param name="desc"></param>
		void SetDesc(const Game3dObjectDesc& desc) { desc_ = &desc; }

#pragma region Set
		void SetStateType(SModelData modelData, ModelFormatType type);
		void SetSkinClusterSrvIndex(const uint32_t& index) { skinClusterSrvIndex_ = index; };
#pragma endregion

#pragma region Get
		uint32_t GetTexHandle() { return texHandle_; }
		uint32_t GetModelHandle() { return modelHandle_; }

		SModelData GetModelData() { return modelData_; }
		Game3dObjectDesc GetDesc() { return *desc_; }
		BufferResource<VertexInfluence>* GetInfluence() { return influence_.get(); }
		BufferResource<uint32_t>* GetVertexNum() { return vertexNum_.get(); }

		uint32_t GetSkinClusterIndex() { return skinClusterSrvIndex_; }
#pragma endregion

	private:

		const Game3dObjectDesc* desc_ = nullptr;

		ModelFormatType formatType_ = OBJECT;

		uint32_t texHandle_ = 0;
		uint32_t modelHandle_ = 0;
		uint32_t prevModelHandle_ = 0;

		unique_ptr<IModelState> state_ = nullptr;
		SModelData modelData_;

		unique_ptr<BufferResource<uint32_t>>vertexNum_;
		uint32_t vertexCountNum_ = 0;

		unique_ptr<BufferResource<VertexInfluence>>influence_;
		vector<VertexInfluence> mappedInfluence;

		uint32_t skinClusterSrvIndex_;
	};

}