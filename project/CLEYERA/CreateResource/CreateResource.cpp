#include "CreateResource.h"

using namespace Engine::Base::DX;
using namespace Engine::Base::Win;
using namespace Engine::Buffer;

ComPtr<ID3D12Resource> CreateResources::CreateBufferResource(size_t sizeInbyte)
{
	ComPtr<ID3D12Device5> device = DirectXCommon::GetInstance()->GetDevice();
    ComPtr<ID3D12Resource> result;


	D3D12_HEAP_PROPERTIES uploadHeapProperties{};
	uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD; //UploadHeap��g��

	//���_���\�[�X�̐ݒ�
	D3D12_RESOURCE_DESC ResourceDesc{};
	ResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	ResourceDesc.Width = sizeInbyte; 
	ResourceDesc.Height = 1;
	ResourceDesc.DepthOrArraySize = 1;
	ResourceDesc.MipLevels = 1;
	ResourceDesc.SampleDesc.Count = 1;
	ResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	
	HRESULT hr = {};
	hr = device->CreateCommittedResource(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE,
		&ResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&result));
	assert(SUCCEEDED(hr));

	return result;
}

void CreateResources::CreateBufferResource(size_t sizeInbyte, ComPtr<ID3D12Resource>& Resource)
{
	ComPtr<ID3D12Device5> device = DirectXCommon::GetInstance()->GetDevice();

	D3D12_HEAP_PROPERTIES uploadHeapProperties{};
	uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;

	D3D12_RESOURCE_DESC ResourceDesc{};
	ResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	ResourceDesc.Width = sizeInbyte;
	ResourceDesc.Height = 1;
	ResourceDesc.DepthOrArraySize = 1;
	ResourceDesc.MipLevels = 1;
	ResourceDesc.SampleDesc.Count = 1;
	ResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	HRESULT hr = {};
	hr = device->CreateCommittedResource(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE,
		&ResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&Resource));
	assert(SUCCEEDED(hr));

}

D3D12_VERTEX_BUFFER_VIEW CreateResources::VertexCreateBufferView(size_t sizeInbyte, ID3D12Resource* Resource, int size)
{
	D3D12_VERTEX_BUFFER_VIEW resultBufferView = {};

	resultBufferView.BufferLocation = Resource->GetGPUVirtualAddress();

	//�g�p���郊�\�[�X�̃T�C�Y�͒��_3���̃T�C�Y
	resultBufferView.SizeInBytes = UINT(sizeInbyte);

	//1���_������̃T�C�Y
	resultBufferView.StrideInBytes = UINT(sizeInbyte / size);
	return resultBufferView; 
}

D3D12_INDEX_BUFFER_VIEW CreateResources::IndexCreateBufferView(size_t sizeInbyte, ComPtr<ID3D12Resource> Resource)
{
	D3D12_INDEX_BUFFER_VIEW resultBufferView = {};

	resultBufferView.BufferLocation = Resource->GetGPUVirtualAddress();

	//�g�p���郊�\�[�X�̃T�C�Y�͒��_3���̃T�C�Y
	resultBufferView.SizeInBytes = UINT(sizeInbyte);

	//1���_������̃T�C�Y
	resultBufferView.Format = DXGI_FORMAT_R32_UINT;

	return resultBufferView;
}
