#pragma once
#include"Pch.h"
#include"DirectXCommon.h"
#include"DescripterData.h"

struct DescriptorSize
{
	uint32_t SRV;
	uint32_t RTV;
	uint32_t DSV;
};

class DescriptorManager
{
public:

	static DescriptorManager* GetInstance();

	static void Initialize();
	static void BeginFlame();
	static void ImGuiUpdate();

	static void Clear();

	static uint32_t CreateSRV(ComPtr<ID3D12Resource>&resource,D3D12_SHADER_RESOURCE_VIEW_DESC SrvDesc);


	/// <summary>
    /// CPU��GPU��ptr����炷
    /// </summary>
	static void CGHandlePtr();

	/// <summary>
	/// indexを増やす
	/// </summary>
	static void IndexIncrement(const string &name);

	static void SetBuffer(const string& name, ComPtr<ID3D12Resource>buf);

	static bool CheckData(const string& name);

	static uint32_t CheckDatasIndex(const string& name);

#pragma region set

	static void SetCPUDescripterHandle(D3D12_CPU_DESCRIPTOR_HANDLE CpuDescripterHandle, uint32_t index)
	{
		DescriptorManager::GetCPUDescriptorHandle(
			DirectXCommon::GetInstance()->GetSrvHeap(),
			index),
		DescriptorManager::GetInstance()->SrvHandleCPU[index] = CpuDescripterHandle;
	}

	static void SetGPUDescripterHandle(D3D12_GPU_DESCRIPTOR_HANDLE GpuDescripterHandle, uint32_t index)
	{
		DescriptorManager::GetInstance()->SrvHandleGPU[index] = GpuDescripterHandle;
	}

#pragma endregion

#pragma region get

	static D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(ComPtr<ID3D12DescriptorHeap> descripterHeap,  uint32_t index);

	static D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(ComPtr<ID3D12DescriptorHeap> descripterHeap, uint32_t index);
	
	static uint32_t GetIndex() { return DescriptorManager::GetInstance()->index; }

	static DescriptorSize GetDescripterSize() { return DescriptorManager::GetInstance()->descripterSize_; }

	static DescripterData* GetData(string name) { return DescriptorManager::GetInstance()->descripterDatas_[name].get(); }

#pragma endregion

#pragma region Command

	/// <summary> 
	/// rootParameter�̃R�}���h�ς�
    /// </summary>
	static void rootParamerterCommand(UINT rootPatramerterIndex, uint32_t texhandle);

	static void CreateShaderResourceView(ID3D12Resource* resource, D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc, uint32_t index);

#pragma endregion
	
private:

	D3D12_CPU_DESCRIPTOR_HANDLE SrvHandleCPU[SRV_DESCRIPTOR_MAX]{};
	D3D12_GPU_DESCRIPTOR_HANDLE SrvHandleGPU[SRV_DESCRIPTOR_MAX]{};

	DescriptorSize descripterSize_{};
	uint32_t index = 0;

	map<string, unique_ptr<DescripterData>>descripterDatas_ = {};

//Singleton
	DescriptorManager() = default;
	~DescriptorManager() = default;
	DescriptorManager(const DescriptorManager&) = delete;
	const  DescriptorManager& operator=(const DescriptorManager&) = delete;
};





