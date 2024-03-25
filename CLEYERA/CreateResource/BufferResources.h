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

	uint32_t bufferNum_ = 1;
	T* param_ = {};
	ComPtr<ID3D12Resource> buffer_ = nullptr;
};

template<typename T>
inline void BufferResource<T>::CreateResource(uint32_t n)
{
	bufferNum_ = n;
	buffer_ = CreateResources::CreateBufferResource(sizeof(T) * n);
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
