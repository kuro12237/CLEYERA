#pragma once
#include"Pch.h"
#include"WinApp.h"
#include"LogManager.h"

#define RTV_DESCRIPTOR_MAX 32
#define SRV_DESCRIPTOR_MAX 64000
#define DSV_DESCRIPTOR_MAX 32

namespace Engine::Base::DX {

	/// <summary>
	/// リークチェック
	/// </summary>
	struct D3DResourceLeakChecker {
		//~D3DResourceLeakChecker() {
		//	ComPtr<IDXGIDebug1>debug;
		//	if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&debug))))
		//	{
		//		debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
		//		debug->ReportLiveObjects(DXGI_DEBUG_APP, DXGI_DEBUG_RLO_ALL);
		//		debug->ReportLiveObjects(DXGI_DEBUG_D3D12, DXGI_DEBUG_RLO_ALL);
		//	}
		//}
	};

	/// <summary>
	/// Command関連
	/// </summary>
	struct Commands {
		ComPtr<ID3D12CommandAllocator>m_pAllocator;
		ComPtr<ID3D12GraphicsCommandList>m_pList;
		ComPtr<ID3D12CommandQueue>m_pQueue;
		D3D12_COMMAND_QUEUE_DESC QueueDesc{};
	};

	/// <summary>
	/// スワップチェーン
	/// </summary>
	struct SwapChain {
		ComPtr<IDXGISwapChain4> m_pSwapChain;
		ComPtr<ID3D12Resource> m_pResource[2];
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	};
	/// <summary>
	/// レンダーターゲット0,1
	/// </summary>
	struct  RTV {
		ComPtr<ID3D12DescriptorHeap> m_pDescritorHeap;
		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
		D3D12_CPU_DESCRIPTOR_HANDLE rtvStartHandle;
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2];
	};

	/// <summary>
	/// DirectXの本体
	/// </summary>
	class DirectXCommon {
	public:

		static DirectXCommon* GetInstance();

		/// <summary>
		/// 初期化
		/// </summary>
		void initialize();
		/// <summary>
		/// 終わり
		/// </summary>
		void Finalize();
		/// <summary>
		/// 描画前
		/// </summary>
		void PreDraw();
		/// <summary>
		/// 描画後
		/// </summary>
		void PostDraw();

		/// <summary>
		/// シザーとビューのコマンド積み
		/// </summary>
		/// <param name="kClientWidth"></param>
		/// <param name="kClientHeight"></param>
		void ScissorViewCommand(const int32_t kClientWidth, const int32_t kClientHeight);

		/// <summary>
		/// ImGui更新
		/// </summary>
		void ImGuiUpdate();

		/// <summary>
		/// コマンド実行
		/// </summary>
		void CommandClosed();

#pragma region get
		Commands GetCommands() { return DirectXCommon::GetInstance()->commands; }
		ID3D12GraphicsCommandList* GetCommandList() { return DirectXCommon::GetInstance()->commands.m_pList.Get(); }
		ID3D12Device5* GetDevice() { return DirectXCommon::GetInstance()->m_pDevice_.Get(); }
		ID3D12DescriptorHeap* GetSrvHeap() { return DirectXCommon::GetInstance()->m_pSrvDescriptorHeap.Get(); }
		ID3D12DescriptorHeap* GetDsvHeap() { return DirectXCommon::GetInstance()->m_pDsvDescripterHeap.Get(); }
		SwapChain GetswapChain() { return DirectXCommon::GetInstance()->swapChain; }
		RTV GetRtv() { return DirectXCommon::GetInstance()->rtv; }
		static float GetFps() { return DirectXCommon::GetInstance()->fps; }
#pragma endregion

	private:
		/// <summary>
		/// ビューの値を入手
		/// </summary>
		D3D12_VIEWPORT viewportSetting(int32_t kClientWidth, int32_t kClientHeight);

		/// <summary>
		/// シザーの値を入手
		/// </summary>
		D3D12_RECT scissorRectSetting(int32_t kClientWidth, int32_t kClientHeight);

		/// <summary>
		/// descripter作成
		/// </summary>
		ComPtr<ID3D12DescriptorHeap> CreateDescripterHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);

		/// <summary>
		///　深度リソース作成
		/// </summary>
		/// <returns></returns>
		ComPtr<ID3D12Resource> CreateDepthStencilTextureResource();

		/// <summary>
		/// でバックレイヤー作成
		/// </summary>
		void CreateDebugLayer();

		/// <summary>
		/// infoQueue作製
		/// </summary>
		void CreateInforQueue();

		/// <summary>
		/// factory作製
		/// </summary>
		void CreateFactory();

		/// <summary>
		/// デバイス作成
		/// </summary>
		void CreateDevice();

		/// <summary>
		/// レイトレーシングをサポートしているか
		/// </summary>
		void CheckRaytracingSuppport();

		/// <summary>
		/// コマンド作成
		/// </summary>
		void CreateCommands();

		/// <summary>
		/// スワップチェーン作成
		/// </summary>
		void CreateSwapChain();

		/// <summary>
		/// でスクリプター作成
		/// </summary>
		void CreateDescritorHeap();

		/// <summary>
		/// スワップチェーンリソース作成
		/// </summary>
		void CreateSwapChainResource();

		/// <summary>
		/// RTV作成
		/// </summary>
		void CreateRTV();

		/// <summary>
		/// フェンス作成
		/// </summary>
		void CreateFence();

		/// <summary>
		/// fps固定作成
		/// </summary>
		void CreateFixFPS();

		/// <summary>
		/// fps更新
		/// </summary>
		void UpdateFixFPS();

		ComPtr<IDXGIFactory7> m_pDxgiFactory_ = nullptr;
		ComPtr<IDXGIAdapter4> m_pUseAdapter_ = nullptr;
		ComPtr<ID3D12Device5>m_pDevice_ = nullptr;
		ComPtr<ID3D12Debug1> m_pDebugController = nullptr;
		ComPtr<ID3D12InfoQueue> infoQueue = nullptr;

		Commands commands = {};
		SwapChain swapChain = {};
		RTV rtv = {};
		ComPtr<ID3D12DescriptorHeap> m_pSrvDescriptorHeap;
		ComPtr<ID3D12DescriptorHeap> m_pDsvDescripterHeap;
		ComPtr<ID3D12Resource> m_pDepthResource = nullptr;
		ComPtr<ID3D12Fence> m_pFence_ = nullptr;
		uint64_t fenceValue = {};
		HANDLE fenceEvent = {};
		D3D12_RESOURCE_BARRIER barrier{};

		chrono::steady_clock::time_point reference_ = {};

		float fps = 0.0f;

		//Singleton
		DirectXCommon() = default;
		~DirectXCommon() = default;
		DirectXCommon(const  DirectXCommon&) = delete;
		const  DirectXCommon& operator=(const DirectXCommon&) = delete;
	};
}
