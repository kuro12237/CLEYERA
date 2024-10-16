#pragma once
#include"DescriptorManager.h"

/// <summary>
/// RTVDescripter管理クラス
/// </summary>
class RTVDescriptorManager
{
public:

	static RTVDescriptorManager* GetInstance();
	
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
	/// 名前があるかをチェック
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	static bool CheckData(const string& name);

	/// <summary>
	/// 名前のindexを返す
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	static uint32_t CheckDatasIndex(const string& name);

	/// <summary>
	/// インデックスを増やす
	/// </summary>
	/// <param name="name"></param>
	static void IndexIncrement(const string& name);

	/// <summary>
	/// リソースと紐づける
	/// </summary>
	/// <param name="resource"></param>
	/// <param name="desc"></param>
	static void AddPointer(ComPtr<ID3D12Resource>resource, D3D12_RENDER_TARGET_VIEW_DESC desc);
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

	map<string, unique_ptr<DescripterData>>datas_ = {};
	//singleton
	RTVDescriptorManager() = default;
	~RTVDescriptorManager() = default;
	RTVDescriptorManager(const  RTVDescriptorManager&) = delete;
	const  RTVDescriptorManager& operator=(const RTVDescriptorManager&) = delete;
};

