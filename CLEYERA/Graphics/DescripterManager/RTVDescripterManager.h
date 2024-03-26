#pragma once
#include"DescriptorManager.h"

class RTVDescriptorManager
{
public:

	static RTVDescriptorManager* GetInstance();

	static void Initialize();
	static void BeginFlame();
	static void ImGuiUpdate();

	static bool CheckData(const string& name);
	static uint32_t CheckDatasIndex(const string& name);


	static void IndexIncrement(const string& name);
	static void AddPointer(ComPtr<ID3D12Resource>resource,D3D12_RENDER_TARGET_VIEW_DESC desc);
#pragma region get
	static 	D3D12_CPU_DESCRIPTOR_HANDLE GetHandle(uint32_t index) { return RTVDescriptorManager::GetInstance()->handle_[index]; }
	static D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index);
	static uint32_t GetIndex() { return RTVDescriptorManager::GetInstance()->index_; }
#pragma endregion

private:

	//0/1はDirectXCommonで使用2から作成開始
	uint32_t index_ = 1;

	D3D12_CPU_DESCRIPTOR_HANDLE handle_[RTV_DESCRIPTOR_MAX];
	uint32_t pointerSize_;

	map<string,unique_ptr<DescripterData>>datas_ = {};
	//singleton
    RTVDescriptorManager() = default;
	~RTVDescriptorManager() = default;
	RTVDescriptorManager(const  RTVDescriptorManager&) = delete;
	const  RTVDescriptorManager& operator=(const RTVDescriptorManager&) = delete;
};

