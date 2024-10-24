#pragma once
#include"CreateResource.h"
#include"BufferResources.h"

namespace System
{
	using namespace Engine::Buffer;

	/// <summary>
	/// スプライト抽象クラス
	/// </summary>
	class ISpriteBuf
	{
	public:
		ISpriteBuf() {};
		~ISpriteBuf() {};

	protected:

		/// <summary>
		/// バッファ作成
		/// </summary>
		void CreateBuf();

		/// <summary>
		/// マップ
		/// </summary>
		void Map();

		void UnMap();

		vector<VertexData>vertexDatas_ = {};
		vector<uint32_t>indexDatas_ = {};
		Material materialDatas_ = {};

		unique_ptr<BufferResource<VertexData>>vertexBuf_ = nullptr;
		unique_ptr<BufferResource<Material>>materialBuf_ = nullptr;
		unique_ptr<BufferResource<uint32_t>>indexBuf_ = nullptr;
	};
};
