#include"Model.h"

Model::Model()
{

}

Model::~Model()
{
}

void Model::DirectXSetDevice(ID3D12Device* device_)
{
	device = device_;
}

void Model::DirectXSetCommands(Commands commands_)
{
	commands = commands_;
}



BufferResource Model::CreateBufferResource(ID3D12Device*device , size_t sizeInbyte)
{
	BufferResource ResultResource;
	//頂点リソース用のヒープの設定
	D3D12_HEAP_PROPERTIES uploadHeapProperties{};

	uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD; //UploadHeapを使う

	//頂点リソースの設定
	D3D12_RESOURCE_DESC vertexResourceDesc{};


	//バッファリソース。テクスチャの場合はまた別の設定をする
	vertexResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	vertexResourceDesc.Width = sizeInbyte; //リソースのサイズ。今回はvector4を3頂点分

	//バッファの場合はこれらは1にする決まり
	vertexResourceDesc.Height = 1;
	vertexResourceDesc.DepthOrArraySize = 1;
	vertexResourceDesc.MipLevels = 1;
	vertexResourceDesc.SampleDesc.Count = 1;

	//バッファの場合はこれにする決まり
	vertexResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	HRESULT hr;
	hr=device->CreateCommittedResource(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE,
		&vertexResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&ResultResource.Resource));
	assert(SUCCEEDED(hr));
	ResultResource.BufferView.BufferLocation = ResultResource.Resource->GetGPUVirtualAddress();

	//使用するリソースのサイズは頂点3つ分のサイズ
	ResultResource.BufferView.SizeInBytes = sizeInbyte;

	//1頂点あたりのサイズ
	ResultResource.BufferView.StrideInBytes = sizeInbyte/3;
	return ResultResource;
}

void Model::CreateVertex(BufferResource &vertex)
{

	vertex = CreateBufferResource(device, sizeof(Vector4) * 3);

}





void Model::Draw(Vector4 top, Vector4 left, Vector4 right, BufferResource &vertex)
{

	Vector4* vertexData = nullptr;


	//書き込むためのアドレスを取得
	vertex.Resource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));

	//左下
	vertexData[0] = { left };

	//上
	vertexData[1] = { top };

	//右上
	vertexData[2] = { right };

	
	commands.List->IASetVertexBuffers(0, 1, &vertex.BufferView);

	//形状を設定。PSOに設定しているものとはまた別。同じものを設定すると考えておけば良い
	commands.List->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//描画(DrawCall/ドローコール)。
	commands.List->DrawInstanced(3, 1, 0, 0);


}

void Model::VartexRelease(BufferResource vartex)
{

	vartex.Resource->Release();

}


