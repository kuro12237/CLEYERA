#pragma once
#include"CreateResource.h"


template<typename T>
class BufferResource
{
public:
	BufferResource() {};
	~BufferResource() { };

	 void CreateResource(uint32_t n = 1);

	 void Map();

	 void Setbuffer(T t) { *param_ = t; }
	 void Setbuffer(vector<T>t);

	 void UnMap();

	 void CommandCall(UINT number);

	 ID3D12Resource* GetBuffer() { return buffer_.Get(); }

private:

	void CreateBufferResource();

	uint32_t bufferNum_ = 1;
	T* param_ = {};
	ComPtr<ID3D12Resource> buffer_ = nullptr;
};

template<typename T>
inline void BufferResource<T>::CreateResource(uint32_t n)
{
	bufferNum_ = n;
	CreateBufferResource();
}

template<typename T>
inline void BufferResource<T>::Map()
{
	buffer_->Map(0, nullptr, reinterpret_cast<void**>(&param_));

}

template<typename T>
inline void BufferResource<T>::Setbuffer(vector<T> t)
{
	for (uint32_t i = 0; i < bufferNum_; i++)
	{
		param_[i] = t[i];
	}
}

template<typename T>
inline void BufferResource<T>::UnMap()
{
	buffer_->Unmap(0, nullptr);
}

template<typename T>
inline void BufferResource<T>::CommandCall(UINT number)
{
	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	commands.m_pList->SetGraphicsRootConstantBufferView(number, buffer_->GetGPUVirtualAddress());
}

template<typename T>
inline void BufferResource<T>::CreateBufferResource()
{
	size_t sizeInbyte = sizeof(T) * bufferNum_;
	ComPtr<ID3D12Device> device = DirectXCommon::GetInstance()->GetDevice();
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
		&ResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&buffer_));
	assert(SUCCEEDED(hr));
}
