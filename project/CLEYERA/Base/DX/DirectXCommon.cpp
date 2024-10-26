#include "DirectXCommon.h"
#include <thread>
#include"Graphics/DescripterManager/DSVDescriptorManager.h"

using namespace Engine;
using namespace Base::DX;
using namespace Base::Win;

DirectXCommon* DirectXCommon::GetInstance() {
	static DirectXCommon instance;
	return &instance;
}

void DirectXCommon::initialize()
{
#ifdef _DEBUG
	CreateDebugLayer();
#endif
	CreateFactory();
	CreateDevice();
	CheckRaytracingSuppport();

#ifdef _DEBUG
	CreateInforQueue();
#endif _DEBUG
	CreateCommands();
	CreateSwapChain();
	CreateDescritorHeap();
	CreateSwapChainResource();
	CreateRTV();
	CreateFence();
	CreateFixFPS();
}

void DirectXCommon::Finalize()
{
	CloseHandle(DirectXCommon::GetInstance()->fenceEvent);
#ifdef _DEBUG
	DirectXCommon::GetInstance()->m_pDebugController->Release();
#endif
}

void DirectXCommon::PreDraw()
{

	UINT backBufferIndex = swapChain.m_pSwapChain->GetCurrentBackBufferIndex();

	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource = swapChain.m_pResource[backBufferIndex].Get();
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;

	commands.m_pList.Get()->ResourceBarrier(1, &barrier);

	//ClearScreen
	commands.m_pList.Get()->OMSetRenderTargets(1, &rtv.rtvHandles[backBufferIndex], false, nullptr);
	float clearColor[] = { 0.1f,0.25f,0.5f,1.0f };
	commands.m_pList.Get()->ClearRenderTargetView(rtv.rtvHandles[backBufferIndex], clearColor, 0, nullptr);

	//Depth
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = m_pDsvDescripterHeap->GetCPUDescriptorHandleForHeapStart();
	commands.m_pList.Get()->OMSetRenderTargets(1, &rtv.rtvHandles[backBufferIndex], false, &dsvHandle);
	commands.m_pList.Get()->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
	ScissorViewCommand(WinApp::GetkCilientWidth(), WinApp::GetkCilientHeight());

}

D3D12_VIEWPORT DirectXCommon::viewportSetting(int32_t kClientWidth, int32_t kClientHeight)
{
	D3D12_VIEWPORT viewport = {};

	viewport.Width = float(kClientWidth);
	viewport.Height = float(kClientHeight);
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	return viewport;
}

D3D12_RECT DirectXCommon::scissorRectSetting(int32_t kClientWidth, int32_t kClientHeight)
{

	D3D12_RECT scissorRect{};
	scissorRect.left = 0;
	scissorRect.right = kClientWidth;
	scissorRect.top = 0;
	scissorRect.bottom = kClientHeight;

	return scissorRect;
}

void DirectXCommon::ScissorViewCommand(const int32_t kClientWidth, const int32_t kClientHeight)
{
	//view
	D3D12_VIEWPORT viewport{};
	viewport = viewportSetting(kClientWidth, kClientHeight);
	//scissor
	D3D12_RECT scissorRect{};
	scissorRect = scissorRectSetting(kClientWidth, kClientHeight);

	commands.m_pList->RSSetViewports(1, &viewport);
	commands.m_pList->RSSetScissorRects(1, &scissorRect);
}

void DirectXCommon::ImGuiUpdate()
{
	if (ImGui::TreeNode("DirectX"))
	{
		ImGui::Text("%f", DirectXCommon::GetFps());
		ImGui::TreePop();
	}

}

void DirectXCommon::CommandClosed()
{
	HRESULT hr = commands.m_pList->Close();
	assert(SUCCEEDED(hr));

	ID3D12CommandList* commandLists[] = { commands.m_pList.Get() };
	commands.m_pQueue->ExecuteCommandLists(1, commandLists);

	fenceValue++;
	//Event
	commands.m_pQueue->Signal(m_pFence_.Get(), fenceValue);
	if (m_pFence_->GetCompletedValue() < fenceValue) {
		HANDLE fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		assert(fenceEvent != nullptr);
		m_pFence_->SetEventOnCompletion(fenceValue, fenceEvent);
		WaitForSingleObject(fenceEvent, INFINITE);
		CloseHandle(fenceEvent);
	}
	//コマンドリセット
	hr = commands.m_pAllocator->Reset();
	assert(SUCCEEDED(hr));
	hr = commands.m_pList->Reset(commands.m_pAllocator.Get(), nullptr);
	assert(SUCCEEDED(hr));
}

void DirectXCommon::PostDraw()
{
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;

	commands.m_pList->ResourceBarrier(1, &barrier);
	HRESULT hr = commands.m_pList->Close();
	assert(SUCCEEDED(hr));

	ID3D12CommandList* commandLists[] = { commands.m_pList.Get() };
	commands.m_pQueue->ExecuteCommandLists(1, commandLists);

	swapChain.m_pSwapChain->Present(1, 0);
	fenceValue++;
	//Event
	commands.m_pQueue->Signal(m_pFence_.Get(), fenceValue);
	if (m_pFence_->GetCompletedValue() < fenceValue) {
		HANDLE fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		assert(fenceEvent != nullptr);
		m_pFence_->SetEventOnCompletion(fenceValue, fenceEvent);
		WaitForSingleObject(fenceEvent, INFINITE);
		CloseHandle(fenceEvent);
	}


	UpdateFixFPS();

	//コマンドリセット
	hr = commands.m_pAllocator->Reset();
	assert(SUCCEEDED(hr));
	hr = commands.m_pList->Reset(commands.m_pAllocator.Get(), nullptr);
	assert(SUCCEEDED(hr));
}

ComPtr<ID3D12DescriptorHeap>  DirectXCommon::CreateDescripterHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible)
{
	ComPtr<ID3D12DescriptorHeap> descriptHeap = nullptr;
	D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc{};
	descriptorHeapDesc.Type = heapType;
	descriptorHeapDesc.NumDescriptors = numDescriptors;

	descriptorHeapDesc.Flags = shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	m_pDevice_->CreateDescriptorHeap(&descriptorHeapDesc, IID_PPV_ARGS(&descriptHeap));
	return descriptHeap;
}

ComPtr<ID3D12Resource>DirectXCommon::CreateDepthStencilTextureResource()
{
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Width = WinApp::GetInstance()->GetkCilientWidth();
	resourceDesc.Height = WinApp::GetInstance()->GetkCilientHeight();
	resourceDesc.MipLevels = 1;
	resourceDesc.DepthOrArraySize = 1;
	resourceDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	resourceDesc.SampleDesc.Count = 1;
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	D3D12_HEAP_PROPERTIES heapProperties{};
	heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;
	D3D12_CLEAR_VALUE depthClearValue{};
	depthClearValue.DepthStencil.Depth = 1.0f;
	depthClearValue.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	ComPtr<ID3D12Resource>resource = nullptr;
	m_pDevice_->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&depthClearValue,
		IID_PPV_ARGS(&resource));

	return resource;
}

void DirectXCommon::CreateInforQueue()
{

	if (SUCCEEDED(m_pDevice_->QueryInterface(IID_PPV_ARGS(&infoQueue))))
	{
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);
		D3D12_MESSAGE_ID denyIds[] =
		{
			D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE
		};
		D3D12_MESSAGE_SEVERITY severities[] = { D3D12_MESSAGE_SEVERITY_INFO };
		D3D12_INFO_QUEUE_FILTER filter{};
		filter.DenyList.NumIDs = _countof(denyIds);
		filter.DenyList.pIDList = denyIds;
		filter.DenyList.NumSeverities = _countof(severities);
		filter.DenyList.pSeverityList = severities;
		infoQueue->PushStorageFilter(&filter);
	}
}

void DirectXCommon::CreateDebugLayer()
{
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&m_pDebugController))))
	{
		m_pDebugController->EnableDebugLayer();
		m_pDebugController->SetEnableGPUBasedValidation(TRUE);
	}
}

void DirectXCommon::CreateFactory()
{

	HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(&m_pDxgiFactory_));
	assert(SUCCEEDED(hr));

	for (UINT i = 0; m_pDxgiFactory_->EnumAdapterByGpuPreference(i,
		DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&m_pUseAdapter_)) !=
		DXGI_ERROR_NOT_FOUND; i++)
	{
		DXGI_ADAPTER_DESC3 adapterDesc{};
		hr = m_pUseAdapter_->GetDesc3(&adapterDesc);
		assert(SUCCEEDED(hr));

		if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE))
		{
			LogManager::Log(LogManager::ConvertString(std::format(L"Use Adapater:{}\n", adapterDesc.Description)));
			break;
		}
		m_pUseAdapter_ = nullptr;
	}
	assert(m_pUseAdapter_ != nullptr);


}

void DirectXCommon::CreateDevice()
{
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_12_2,D3D_FEATURE_LEVEL_12_1,D3D_FEATURE_LEVEL_12_0
	};

	const char* featureLevelStrings[] = { "12.2","12.1","12.0" };

	for (size_t i = 0; i < _countof(featureLevels); i++)
	{
		HRESULT hr = D3D12CreateDevice(
			m_pUseAdapter_.Get(),
			featureLevels[i],
			IID_PPV_ARGS(&m_pDevice_));
		if (SUCCEEDED(hr))
		{
			LogManager::Log(std::format("FeatureLevel : {}\n", featureLevelStrings[i]));
			break;
		}
	}

	assert(m_pDevice_ != nullptr);
}

void Engine::Base::DX::DirectXCommon::CheckRaytracingSuppport()
{
	D3D12_FEATURE_DATA_D3D12_OPTIONS5 options{};
	HRESULT hr = this->m_pDevice_->CheckFeatureSupport(
		D3D12_FEATURE_D3D12_OPTIONS5, &options, sizeof(options));

	if (FAILED(hr) || options.RaytracingTier == D3D12_RAYTRACING_TIER_NOT_SUPPORTED)
	{
		throw std::runtime_error("DirectX Raytracing not support");
	}
}

void DirectXCommon::CreateCommands()
{

	commands.m_pQueue = nullptr;
	HRESULT hr = m_pDevice_->CreateCommandQueue(&commands.QueueDesc, IID_PPV_ARGS(&commands.m_pQueue));
	assert(SUCCEEDED(hr));

	commands.m_pAllocator = nullptr;
	hr = m_pDevice_->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commands.m_pAllocator));
	assert(SUCCEEDED(hr));

	commands.m_pList = nullptr;
	hr = m_pDevice_->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT,
		commands.m_pAllocator.Get(), nullptr,
		IID_PPV_ARGS(&commands.m_pList));
	assert(SUCCEEDED(hr));

}

void DirectXCommon::CreateSwapChain()
{
	HWND hwnd_ = WinApp::GetInstance()->GetHwnd();

	swapChain.swapChainDesc.Width = WinApp::GetInstance()->GetkCilientWidth();
	swapChain.swapChainDesc.Height = WinApp::GetInstance()->GetkCilientHeight();
	swapChain.swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChain.swapChainDesc.SampleDesc.Count = 1;
	swapChain.swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChain.swapChainDesc.BufferCount = 2;
	swapChain.swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	m_pDxgiFactory_.Get()->
		CreateSwapChainForHwnd(commands.m_pQueue.Get(), hwnd_, &swapChain.swapChainDesc,
			nullptr, nullptr, reinterpret_cast<IDXGISwapChain1**>(&swapChain));

}

void DirectXCommon::CreateDescritorHeap()
{
	rtv.m_pDescritorHeap =
		CreateDescripterHeap(D3D12_DESCRIPTOR_HEAP_TYPE_RTV, RTV_DESCRIPTOR_MAX, false);
	m_pSrvDescriptorHeap =
		CreateDescripterHeap(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, SRV_DESCRIPTOR_MAX, true);
	m_pDsvDescripterHeap =
		CreateDescripterHeap(D3D12_DESCRIPTOR_HEAP_TYPE_DSV, DSV_DESCRIPTOR_MAX, false);

	m_pDepthResource =
		CreateDepthStencilTextureResource();

	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
	dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;

	m_pDevice_->CreateDepthStencilView(
		m_pDepthResource.Get(), &dsvDesc,
		m_pDsvDescripterHeap->GetCPUDescriptorHandleForHeapStart()
	);

}

void DirectXCommon::CreateSwapChainResource()
{
	HRESULT hr = swapChain.m_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&swapChain.m_pResource[0]));
	assert(SUCCEEDED(hr));

	hr = swapChain.m_pSwapChain->GetBuffer(1, IID_PPV_ARGS(&swapChain.m_pResource[1]));
	assert(SUCCEEDED(hr));
}

void DirectXCommon::CreateRTV()
{

	rtv.rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	rtv.rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	rtv.rtvStartHandle = rtv.m_pDescritorHeap->GetCPUDescriptorHandleForHeapStart();
	rtv.rtvHandles[0] = rtv.rtvStartHandle;
	m_pDevice_->CreateRenderTargetView(swapChain.m_pResource[0].Get(), &rtv.rtvDesc, rtv.rtvHandles[0]);
	rtv.rtvHandles[1].ptr = rtv.rtvHandles[0].ptr + m_pDevice_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	m_pDevice_->CreateRenderTargetView(swapChain.m_pResource[1].Get(), &rtv.rtvDesc, rtv.rtvHandles[1]);

}

void DirectXCommon::CreateFence()
{
	m_pDevice_->CreateFence(fenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_pFence_));
	fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	assert(fenceEvent != nullptr);
}

void DirectXCommon::CreateFixFPS()
{
	DirectXCommon::GetInstance()->reference_ = steady_clock::now();
}

void DirectXCommon::UpdateFixFPS()
{
	const microseconds kMinTime(uint64_t(1000000.0f / 60.0f));

	const microseconds kMinCheckTime(uint64_t(1000000.0f / 65.0f));

	steady_clock::time_point now = steady_clock::now();

	microseconds elapsed =
		duration_cast<microseconds>(now - DirectXCommon::GetInstance()->reference_);
	DirectXCommon::GetInstance()->fps = 1000000.0f / static_cast<float>(elapsed.count());
	//1/60
	if (elapsed < kMinTime)
	{

		while (steady_clock::now() - DirectXCommon::GetInstance()->reference_ < kMinCheckTime)
		{
			std::this_thread::sleep_for(microseconds(1));
		}
	}
	DirectXCommon::GetInstance()->reference_ = steady_clock::now();
}

