#include"Model.h"

Model::Model()
{
	matrixTransform_ = new MatrixTransform();
	vectorTransform_ = new VectorTransform();

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



ID3D12Resource* Model::CreateBufferResource(ID3D12Device*device , size_t sizeInbyte)
{
	ID3D12Resource* RssultResource;
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
		&vertexResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&RssultResource));
	assert(SUCCEEDED(hr));

	return RssultResource;
}

D3D12_VERTEX_BUFFER_VIEW Model::CreateBufferVier(size_t sizeInbyte,ID3D12Resource* Resource)
{
	D3D12_VERTEX_BUFFER_VIEW resultBufferView;

	resultBufferView.BufferLocation = Resource->GetGPUVirtualAddress();

	//使用するリソースのサイズは頂点3つ分のサイズ
	resultBufferView.SizeInBytes = sizeInbyte;

	//1頂点あたりのサイズ
	resultBufferView.StrideInBytes = sizeInbyte / 3;
	return resultBufferView;
}



void Model::CreateVertex(BufferResource &Resource)
{

	Resource.Vertex = CreateBufferResource(device, sizeof(Vector4) * 3);
	Resource.Material = CreateBufferResource(device, sizeof(Vector4));
	Resource.wvpResource = CreateBufferResource(device, sizeof(Matrix4x4));
	Resource.BufferView = CreateBufferVier(sizeof(Vector4) * 3,Resource.Vertex);
}






void Model::Draw(Vector4 top, Vector4 left, Vector4 right, unsigned int ColorCode,Matrix4x4 matrixTransform,BufferResource &Resource)
{

	Vector4* vertexData = nullptr;
	Vector4* MaterialData = nullptr;
	Matrix4x4* wvpData = nullptr;
	//書き込むためのアドレスを取得
	Resource.Vertex->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	Resource.Material->Map(0, nullptr, reinterpret_cast<void**>(&MaterialData));
	Resource.wvpResource->Map(0, nullptr, reinterpret_cast<void**>(&wvpData));
    
	//座標
	//左下
	vertexData[0] = { left };

	//上
	vertexData[1] = { top };

	//右上
	vertexData[2] = { right };

	//マテリアル
	Vector4 colorData = ColorAdapter(ColorCode);

	*MaterialData = colorData;
	//
	//Scene返還
	//行列の変換

	Transform camera={ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,-5.0f} };

	Matrix4x4 projectionMatrix = matrixTransform_->MakePerspectiveFovMatrix(0.45, 1280.0f / 720.0f, 0.1f, 100.0f);
	Matrix4x4 cameraMatrix = matrixTransform_->MakeAffineMatrix(camera.scale, camera.rotate, camera.translate);
	Matrix4x4 viewMatrix = matrixTransform_->Inverse(cameraMatrix);

	Matrix4x4 worldViewProjectionMatrix = matrixTransform_->Multiply(matrixTransform, matrixTransform_->Multiply(viewMatrix, projectionMatrix));

	*wvpData = worldViewProjectionMatrix;
	//*wvpData = worldViewProjectionMatrix;

	commands.List->IASetVertexBuffers(0, 1, &Resource.BufferView);

	//形状を設定。PSOに設定しているものとはまた別。同じものを設定すると考えておけば良い
	commands.List->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	//マテリアルCBufferの場所を設定
	commands.List->SetGraphicsRootConstantBufferView(0, Resource.Material->GetGPUVirtualAddress());
	
	//wvp用のCBufferの場所を設定
	commands.List->SetGraphicsRootConstantBufferView(1, Resource.wvpResource->GetGPUVirtualAddress());

	//描画(DrawCall/ドローコール)。
	commands.List->DrawInstanced(3, 1, 0, 0);


}

void Model::VartexRelease(BufferResource Resource)
{

	Resource.Vertex->Release();
	Resource.Material->Release();
	Resource.wvpResource->Release();
}

Vector4 Model::ColorAdapter(unsigned int color)
{
	Vector4 ResultColor = {
     
	   ((color >> 24) & 0xFF) / 255.0f, // 赤
     
	   ((color >> 16) & 0xFF) / 255.0f, // 緑
     
	   ((color >>8) & 0xFF) / 255.0f,  // 青
     
	   ((color) & 0xFF) / 255.0f //透明度
     
    };
     
     return ResultColor;
	
}


