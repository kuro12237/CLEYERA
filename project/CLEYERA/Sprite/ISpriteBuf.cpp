#include "ISpriteBuf.h"

void System::ISpriteBuf::CreateBuf()
{
	vertexBuf_ = make_unique<BufferResource<VertexData>>();
	vertexBuf_->CreateResource(4);
	vertexBuf_->CreateVertexBufferView();

	indexBuf_ = make_unique<BufferResource<uint32_t>>();
	indexBuf_->CreateResource(6);
	indexBuf_->CreateIndexBufferView();

	materialBuf_ = make_unique<BufferResource<Material>>();
	materialBuf_->CreateResource();
}

void System::ISpriteBuf::Map()
{
	vertexBuf_->Map();
	indexBuf_->Map();
	materialBuf_->Map();
}

void System::ISpriteBuf::UnMap()
{
	vertexBuf_->UnMap();
	indexBuf_->UnMap();
	materialBuf_->UnMap();
}
