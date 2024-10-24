#pragma once
#include"DirectXCommon.h"
#include"DescripterData.h"

class DSVDescriptorManager
{
public:

	static DSVDescriptorManager* GetInstance();

	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	static void Initialize();

	/// <summary>
	/// –ˆƒtƒŒ[ƒ€‚Ìn‚Ü‚è
	/// </summary>
	static void BeginFlame();


	static void ImGuiUpdate();

	static void IndexIncrement(const string &name);
	static void AddPointer(ComPtr<ID3D12Resource>resource, D3D12_DEPTH_STENCIL_VIEW_DESC desc);

	static bool CheckData(const string& name);

	static uint32_t CheckDatasIndex(const string& name);

#pragma region Get

	static D3D12_CPU_DESCRIPTOR_HANDLE GetHandle(uint32_t index) { return DSVDescriptorManager::GetInstance()->handle_[index]; }

	static D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index);

	static 	uint32_t GetSize() { return DSVDescriptorManager::GetInstance()->pointerSize_; }
	static uint32_t GetIndex() { return DSVDescriptorManager::GetInstance()->index; }

#pragma endregion

	static void SetCPUDescripterHandle(D3D12_CPU_DESCRIPTOR_HANDLE CpuDescripterHandle, uint32_t index)
	{
		DSVDescriptorManager::GetInstance()->handle_[index] = CpuDescripterHandle;
	}



private:

	uint32_t index = 0;
	D3D12_CPU_DESCRIPTOR_HANDLE handle_[DSV_DESCRIPTOR_MAX];
	uint32_t pointerSize_;

	map<string,unique_ptr<DescripterData>> datas_ = {};

	//singleton
	DSVDescriptorManager() = default;
	~DSVDescriptorManager() = default;
	DSVDescriptorManager(const  DSVDescriptorManager&) = delete;
	const  DSVDescriptorManager& operator=(const DSVDescriptorManager&) = delete;
};