#pragma once
#include"CreateResource.h"
#include"BufferResources.h"

namespace System
{
	class ISpriteBuf
	{
	public:
		ISpriteBuf() {};
		~ISpriteBuf() {};

	protected:

		void CreateBuf();

		void Map();

		void unMap();

		vector<VertexData>vertexDatas_ = {};
		vector<uint32_t>indexDatas_ = {};
		Material materialDatas_ = {};

		unique_ptr<BufferResource<VertexData>>vertexBuf_ = nullptr;
		unique_ptr<BufferResource<Material>>materialBuf_ = nullptr;
		unique_ptr<BufferResource<uint32_t>>indexBuf_ = nullptr;
	};
};