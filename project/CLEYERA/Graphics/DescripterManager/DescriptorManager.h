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

/// <summary>
/// SRVDescripter管理クラス
/// </summary>
class DescriptorManager
{
public:

	static DescriptorManager* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	static void Initialize();

	/// <summary>
	/// 毎フレームのはじめ
	/// </summary>
	static void BeginFlame();

	/// <summary>
	/// ImGui更新
	/// </summary>
	static void ImGuiUpdate();

	/// <summary>
	/// データを削除
	/// </summary>
	static void Clear();

	/// <summary>
	/// SRV作製
	/// </summary>
	/// <param name="resource"></param>
	/// <param name="SrvDesc"></param>
	/// <returns></returns>
	static uint32_t CreateSRV(ComPtr<ID3D12Resource>&resource,D3D12_SHADER_RESOURCE_VIEW_DESC SrvDesc);

	/// <summary>
	/// UAV作製
	/// </summary>
	/// <param name="resource"></param>
	/// <param name="desc"></param>
	/// <returns></returns>
	uint32_t CreateUAV(ComPtr<ID3D12Resource>& resource, D3D12_UNORDERED_ACCESS_VIEW_DESC desc);

	/// <summary>
    /// ポインタをブラス
    /// </summary>
	static void CGHandlePtr();

	/// <summary>
	/// indexを増やす
	/// </summary>
	static void IndexIncrement(const string &name);

	/// <summary>
	/// 名前とバッファを登録
	/// </summary>
	/// <param name="name"></param>
	/// <param name="buf"></param>
	static void SetBuffer(const string& name, ComPtr<ID3D12Resource>buf);

	/// <summary>
	/// 登録されているかをチェック
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	static bool CheckData(const string& name);

	/// <summary>
	/// 名前のインデックスを返す
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	static uint32_t CheckDatasIndex(const string& name);

#pragma region set

	static void SetCPUDescripterHandle(D3D12_CPU_DESCRIPTOR_HANDLE CpuDescripterHandle, uint32_t index)
	{
		DescriptorManager::GetCPUDescriptorHandle(
			index),
		DescriptorManager::GetInstance()->SrvHandleCPU[index] = CpuDescripterHandle;
	}

	static void SetGPUDescripterHandle(D3D12_GPU_DESCRIPTOR_HANDLE GpuDescripterHandle, uint32_t index)
	{
		DescriptorManager::GetInstance()->SrvHandleGPU[index] = GpuDescripterHandle;
	}

#pragma endregion

#pragma region get

	static D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(uint32_t index);

	static D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(uint32_t index);
	
	static uint32_t GetIndex() { return DescriptorManager::GetInstance()->index; }

	static DescriptorSize GetDescripterSize() { return DescriptorManager::GetInstance()->descripterSize_; }

	static DescripterData* GetData(string name) { return DescriptorManager::GetInstance()->descripterDatas_[name].get(); }

#pragma endregion

#pragma region Command

	/// <summary> 
	/// rootParameterを積む
    /// </summary>
	static void rootParamerterCommand(UINT rootPatramerterIndex, uint32_t texhandle);

	/// <summary>
	/// CSの時に使う
	/// </summary>
	/// <param name="rootParamIndex"></param>
	/// <param name="index"></param>
	void ComputeRootParamerterCommand(UINT rootParamIndex, uint32_t index);

	/// <summary>
	/// SRVトresourceを紐づける
	/// </summary>
	/// <param name="resource"></param>
	/// <param name="srvDesc"></param>
	/// <param name="index"></param>
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





