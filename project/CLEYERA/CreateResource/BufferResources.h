#pragma once
#include"Graphics/DescripterManager/DescriptorManager.h"
#include"Graphics/DescripterManager/RTVDescripterManager.h"
#include"Graphics/DescripterManager/DSVDescriptorManager.h"
#include"Pch.h"

namespace Engine::Buffer
{
	
	template<typename T>
	/// <summary>
	/// ComPtrを使用したBuffer作製Descripterの確保のクラス
	/// </summary>
	class BufferResource
	{
	public:
		BufferResource() {};
		~BufferResource() {};

		void CreateResource(uint32_t n = 1);

		void CreateVertexBufferView();
		void CreateIndexBufferView();

		void Map();
		void UnMap();

		void Setbuffer(T t) { *param_ = t; }
		void Setbuffer(vector<T>t);
		void Setbuffer(vector<T>t, uint32_t num);

		void CommandCall(UINT number);
		void ComputeCommandCall(UINT number);

		void CommandVertexBufferViewCall(uint32_t view = 1);
		void CommandIndexBufferViewCall();
		void CommandPrimitiveTopologyCall();

#pragma region 書き込みリソース

		/// <summary>
		/// 書き込みリソース
		/// </summary>
		void CreateResource(DXGI_FORMAT format, const int32_t width, const int32_t height);

		void CreateResource(D3D12_RESOURCE_DESC resourceDesc, D3D12_HEAP_PROPERTIES heapPram, D3D12_RESOURCE_STATES state, D3D12_CLEAR_VALUE depthClearValue);

		void CreateInstancingResource(const uint32_t& instancingNum, const string& Name, UINT size);

		void CreateUAVResource(const uint32_t& Num, const string& Name, UINT size);

		/// <summary>
		/// 画像bufferを更新
		/// </summary>
		void TransfarImage(const UINT pixCount, const UINT rowPitch, const UINT depthPitch);

		/// <summary>
		/// srvに登録
		/// </summary>
		void RegisterSRV(DXGI_FORMAT format, const string& name);

		void RegisterRTV(DXGI_FORMAT format, const string& name);

		void RegisterDSV(DXGI_FORMAT format, const string& name);

#pragma endregion

#pragma region Get

		ID3D12Resource* GetBuffer() { return buffer_.Get(); }

		uint32_t GetSrvIndex() { return srvIndex_; }
		uint32_t GetRtvIndex() { return rtvIndex_; }
		uint32_t GetDsvIndex() { return dsvIndex_; }

		D3D12_VERTEX_BUFFER_VIEW GetBufferView() { return vertexBufferView_; }

#pragma endregion

	private:

		void CreateBufferResource();

		uint32_t srvIndex_ = 0;
		uint32_t rtvIndex_ = 0;
		uint32_t dsvIndex_ = 0;
		uint32_t bufferNum_ = 1;
		T* param_ = {};

		ComPtr<ID3D12Resource> buffer_ = nullptr;
		D3D12_VERTEX_BUFFER_VIEW vertexBufferView_{};
		D3D12_INDEX_BUFFER_VIEW indexBufferView_{};
	};

	template<typename T>
	inline void BufferResource<T>::CreateResource(uint32_t n)
	{
		bufferNum_ = n;
		CreateBufferResource();
	}

	template<typename T>
	inline void BufferResource<T>::CreateResource(DXGI_FORMAT format, const int32_t width, const int32_t height)
	{
		//resourceDesc設定
		D3D12_RESOURCE_DESC resourceDesc = {};
		resourceDesc.Width = width;
		resourceDesc.Height = height;
		resourceDesc.MipLevels = 1;
		resourceDesc.DepthOrArraySize = 1;
		resourceDesc.Format = format;
		resourceDesc.SampleDesc.Count = 1;
		resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		resourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

		//Heap設定
		D3D12_HEAP_PROPERTIES heapPram{};
		heapPram.Type = D3D12_HEAP_TYPE_CUSTOM;
		heapPram.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
		heapPram.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;

		//色
		D3D12_CLEAR_VALUE color = {};

		const float clearColor[4] = { 0.25f,0.5f,0.1f,0.0f };

		color.Format = format;
		for (uint32_t i = 0; i < 4; i++)
		{
			color.Color[i] = clearColor[i];
		}

		//後で下を関数化
		ComPtr<ID3D12Device5>device = Engine::Base::DX::DirectXCommon::GetInstance()->GetDevice();
		device->CreateCommittedResource(
			&heapPram,
			D3D12_HEAP_FLAG_NONE,
			&resourceDesc,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
			&color,
			IID_PPV_ARGS(&buffer_)
		);

	}

	template<typename T>
	inline void BufferResource<T>::CreateResource(D3D12_RESOURCE_DESC resourceDesc, D3D12_HEAP_PROPERTIES heapPram, D3D12_RESOURCE_STATES state, D3D12_CLEAR_VALUE depthClearValue)
	{
		//色
		D3D12_CLEAR_VALUE color = depthClearValue;

		//後で下を関数化
		ComPtr<ID3D12Device5>device = Engine::Base::DX::DirectXCommon::GetInstance()->GetDevice();
		device->CreateCommittedResource(
			&heapPram,
			D3D12_HEAP_FLAG_NONE,
			&resourceDesc,
			state,
			&color,
			IID_PPV_ARGS(&buffer_)
		);
	}



	template<typename T>
	inline void BufferResource<T>::CreateVertexBufferView()
	{

		vertexBufferView_.BufferLocation = buffer_->GetGPUVirtualAddress();
		vertexBufferView_.SizeInBytes = UINT(sizeof(T) * bufferNum_);
		vertexBufferView_.StrideInBytes = UINT(sizeof(T));
	}

	template<typename T>
	inline void BufferResource<T>::CreateIndexBufferView()
	{
		indexBufferView_.BufferLocation = buffer_->GetGPUVirtualAddress();
		indexBufferView_.SizeInBytes = UINT(sizeof(T) * bufferNum_);
		indexBufferView_.Format = DXGI_FORMAT_R32_UINT;
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
	inline void BufferResource<T>::Setbuffer(vector<T> t, uint32_t num)
	{
		for (uint32_t i = 0; i < num; i++)
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
		ID3D12GraphicsCommandList* list = Engine::Base::DX::DirectXCommon::GetInstance()->GetCommandList();
		list->SetGraphicsRootConstantBufferView(number, buffer_->GetGPUVirtualAddress());
	}

	template<typename T>
	inline void BufferResource<T>::ComputeCommandCall(UINT number)
	{
		ID3D12GraphicsCommandList* list = Engine::Base::DX::DirectXCommon::GetInstance()->GetCommandList();
		list->SetComputeRootConstantBufferView(number, buffer_->GetGPUVirtualAddress());
	}

	template<typename T>
	inline void BufferResource<T>::CommandVertexBufferViewCall(uint32_t view)
	{
		ID3D12GraphicsCommandList* list = Engine::Base::DX::DirectXCommon::GetInstance()->GetCommandList();
		list->IASetVertexBuffers(0, view, &vertexBufferView_);
	}

	template<typename T>
	inline void BufferResource<T>::CommandIndexBufferViewCall()
	{
		ID3D12GraphicsCommandList* list = Engine::Base::DX::DirectXCommon::GetInstance()->GetCommandList();
		list->IASetIndexBuffer(&indexBufferView_);
	}

	template<typename T>
	inline void BufferResource<T>::CommandPrimitiveTopologyCall()
	{
		ID3D12GraphicsCommandList* list = Engine::Base::DX::DirectXCommon::GetInstance()->GetCommandList();
		list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	template<typename T>
	inline void BufferResource<T>::TransfarImage(const UINT pixCount, const UINT rowPitch, const UINT depthPitch)
	{
		UINT* img = new UINT[pixCount];
		for (int i = 0; i < int(pixCount); i++)
		{
			img[i] = 0xff0000ff;
		}
		HRESULT hr = {};
		hr = buffer_->WriteToSubresource(
			0,
			nullptr,
			img,
			rowPitch,
			depthPitch
		);
		assert(SUCCEEDED(hr));
		delete[] img;
	}

	template<typename T>
	inline void BufferResource<T>::RegisterSRV(DXGI_FORMAT format, const string& name)
	{
		if (DescriptorManager::CheckData(name))
		{
			//Despcripter
			DescriptorManager::IndexIncrement(name);
			uint32_t index = DescriptorManager::GetIndex();

			D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = { };
			srvDesc.Format = format;
			srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
			srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Texture2D.MipLevels = 1;

			DescriptorManager::SetCPUDescripterHandle(
				DescriptorManager::GetCPUDescriptorHandle(
					index),
				index
			);

			DescriptorManager::SetGPUDescripterHandle(
				DescriptorManager::GetGPUDescriptorHandle(
					index),
				index
			);

			DescriptorManager::CGHandlePtr();
			DescriptorManager::CreateShaderResourceView(
				buffer_.Get(),
				srvDesc,
				index);
			srvIndex_ = index;
		}
		else if (!DescriptorManager::CheckData(name))
		{
			srvIndex_ = DescriptorManager::CheckDatasIndex(name);
		}
	}

	template<typename T>
	inline void BufferResource<T>::RegisterRTV(DXGI_FORMAT format, const string& name)
	{
		if (RTVDescriptorManager::CheckData(name))
		{
			D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
			rtvDesc.Format = format;
			rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
			RTVDescriptorManager::IndexIncrement(name);
			rtvIndex_ = RTVDescriptorManager::GetIndex();
			RTVDescriptorManager::AddPointer(buffer_, rtvDesc);
		}
		else if (!RTVDescriptorManager::CheckDatasIndex(name))
		{
			rtvIndex_ = RTVDescriptorManager::CheckDatasIndex(name);
		}
	}

	template<typename T>
	inline void BufferResource<T>::RegisterDSV(DXGI_FORMAT format, const string& name)
	{
		D3D12_DEPTH_STENCIL_VIEW_DESC desc{};
		desc.Format = format;
		desc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;

		DSVDescriptorManager::IndexIncrement(name);
		dsvIndex_ = DSVDescriptorManager::GetIndex();
		DSVDescriptorManager::AddPointer(buffer_, desc);
	}

	template<typename T>
	inline void BufferResource<T>::CreateBufferResource()
	{
		size_t sizeInbyte = sizeof(T) * bufferNum_;
		ComPtr<ID3D12Device5> device = Engine::Base::DX::DirectXCommon::GetInstance()->GetDevice();
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

	template<typename T>
	inline void BufferResource<T>::CreateInstancingResource(const uint32_t& instancingNum, const string& Name, UINT size)
	{
		if (DescriptorManager::CheckData(Name))
		{
			DescriptorManager::IndexIncrement(Name);
			DescriptorManager::SetBuffer(Name, buffer_);

			D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc;
			srvDesc.Format = DXGI_FORMAT_UNKNOWN;
			srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
			srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
			srvDesc.Buffer.FirstElement = 0;
			srvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;;
			srvDesc.Buffer.NumElements = instancingNum;
			srvDesc.Buffer.StructureByteStride = size;

			srvIndex_ = DescriptorManager::CreateSRV(buffer_, srvDesc);
		}
		else {
			buffer_ = DescriptorManager::GetData(Name)->GetBuf();
			srvIndex_ = DescriptorManager::GetData(Name)->GetIndex();
		}
	}

	template<typename T>
	inline void BufferResource<T>::CreateUAVResource(const uint32_t& Num, const string& Name, UINT size)
	{

		if (DescriptorManager::CheckData(Name))
		{
			{//buffer作成
				bufferNum_ = Num;
				size_t sizeInbyte = sizeof(T) * bufferNum_;
				ComPtr<ID3D12Device5> device = Engine::Base::DX::DirectXCommon::GetInstance()->GetDevice();
				D3D12_HEAP_PROPERTIES uploadHeapProperties{};
				uploadHeapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;

				D3D12_RESOURCE_DESC ResourceDesc{};
				ResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
				ResourceDesc.Width = sizeInbyte;
				ResourceDesc.Height = 1;
				ResourceDesc.DepthOrArraySize = 1;
				ResourceDesc.MipLevels = 1;
				ResourceDesc.SampleDesc.Count = 1;
				ResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
				ResourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
				HRESULT hr = {};
				hr = device->CreateCommittedResource(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE,
					&ResourceDesc, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&buffer_));
				assert(SUCCEEDED(hr));
			}

			DescriptorManager::IndexIncrement(Name);
			DescriptorManager::SetBuffer(Name, buffer_);

			D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc{};
			uavDesc.Format = DXGI_FORMAT_UNKNOWN;
			uavDesc.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
			uavDesc.Buffer.FirstElement = 0;
			uavDesc.Buffer.NumElements = bufferNum_;
			uavDesc.Buffer.CounterOffsetInBytes = 0;
			uavDesc.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_NONE;
			uavDesc.Buffer.StructureByteStride = size;

			srvIndex_ = DescriptorManager::GetInstance()->CreateUAV(buffer_, uavDesc);
		}
		else {
			buffer_ = DescriptorManager::GetData(Name)->GetBuf();
			srvIndex_ = DescriptorManager::GetData(Name)->GetIndex();
		}
	}
}