#include "DeferredShading.h"

void DefferredShading::Initialize()
{
	vertexBuffer_ = make_unique<BufferResource<VertexData>>();
	vertexBuffer_->CreateResource(4);

	materialBuffer_ = make_unique<BufferResource<Material>>();
	materialBuffer_->CreateResource();

	indexBuffer_ = make_unique<BufferResource<uint32_t>>();
	indexBuffer_->CreateResource(6);
	indexBuffer_->CreateIndexBufferView();

	CreateTexBuffer();

}

void DefferredShading::PreColorDraw()
{
	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	// レンダーターゲットをセット
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = RTVDescriptorManager::GetHandle(colorTexBuffer_->GetRtvIndex());
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = DSVDescriptorManager::GetHandle(depthBuffer_->GetDsvIndex());
	D3D12_RESOURCE_BARRIER barrier{};
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource = colorTexBuffer_->GetBuffer();
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
	commands.m_pList->ResourceBarrier(1, &barrier);
	commands.m_pList->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);

	CommandCallView(static_cast<float>(WinApp::GetkCilientWidth()), static_cast<float>(WinApp::GetkCilientHeight()));
	CommandCallScissor();

	const float clearColor[4] = { 0.25f,0.5f,0.1f,0.0f };

	commands.m_pList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
	commands.m_pList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void DefferredShading::PostColorDraw()
{
	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	D3D12_RESOURCE_BARRIER barrier{};
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.Subresource = 0xFFFFFFFF;
	barrier.Transition.pResource = colorTexBuffer_->GetBuffer();
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
	DirectXCommon::GetInstance()->GetCommands().m_pList->ResourceBarrier(1, &barrier);
}

void DefferredShading::Draw(const WorldTransform& worldTransform, const CameraData& camera)
{
	worldTransform, camera;
	ComPtr<ID3D12GraphicsCommandList> m_pList = DirectXCommon::GetInstance()->GetCommands().m_pList;

	vertexBuffer_->CommandVertexBufferViewCall();
	indexBuffer_->CommandIndexBufferViewCall();

    m_pList->DrawIndexedInstanced(6,1, 0, 0, 0);
}


void DefferredShading::CreateTexBuffer()
{
	DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	//texSize
	const UINT pixCount = WinApp::GetkCilientWidth() * WinApp::GetkCilientHeight();
	const UINT rowPitch = sizeof(UINT) * WinApp::GetkCilientWidth();
	const UINT depthPitch = rowPitch * WinApp::GetkCilientHeight();

	//カラーテクスチャ
	colorTexBuffer_ = make_unique<BufferResource<uint32_t>>();
	colorTexBuffer_->CreateResource(format, WinApp::GetkCilientWidth(), WinApp::GetkCilientHeight());
	colorTexBuffer_->TransfarImage(pixCount,rowPitch,depthPitch);
	colorTexBuffer_->RegisterSRV(format, "DeferredShadingColor");
	colorTexBuffer_->RegisterRTV(format, "DeferredShadingColor");

	//法線テクスチャ
	normalTexBuffer_ = make_unique<BufferResource<uint32_t>>();
	normalTexBuffer_->CreateResource(format, WinApp::GetkCilientWidth(), WinApp::GetkCilientHeight());
	normalTexBuffer_->TransfarImage(pixCount, rowPitch, depthPitch);
	normalTexBuffer_->RegisterSRV(format, "DeferredShadingNormal");
	normalTexBuffer_->RegisterRTV(format, "DeferredShadingNormal");

	depthBuffer_ = make_unique<BufferResource<uint32_t>>();
	depthBuffer_->RegisterDSV(DXGI_FORMAT_D32_FLOAT, "DeferredShadingDepth");

}


void DefferredShading::CommandCallView(const float& width, const float& height)
{
	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	D3D12_VIEWPORT viewport{};
	viewport.Width = width;
	viewport.Height = height;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	commands.m_pList->RSSetViewports(1, &viewport);
}


void DefferredShading::CommandCallScissor()
{
	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	D3D12_RECT scissorRect{};
	scissorRect.left = 0;
	scissorRect.right = (WinApp::GetkCilientWidth());
	scissorRect.top = 0;
	scissorRect.bottom = WinApp::GetkCilientHeight();

	commands.m_pList->RSSetScissorRects(1, &scissorRect);
}