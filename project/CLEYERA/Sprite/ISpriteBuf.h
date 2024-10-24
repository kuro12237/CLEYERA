#pragma once
#include"CreateResource.h"
#include"BufferResources.h"

namespace System
{
	using namespace Engine::Buffer;

	/// <summary>
	/// �X�v���C�g���ۃN���X
	/// </summary>
	class ISpriteBuf
	{
	public:
		ISpriteBuf() {};
		~ISpriteBuf() {};

	protected:

		/// <summary>
		/// �o�b�t�@�쐬
		/// </summary>
		void CreateBuf();

		/// <summary>
		/// �}�b�v
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
