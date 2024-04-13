#include "DeferredShading.h"

void DefferredShading::Initialize()
{
	vertexBuffer_ = make_unique<BufferResource<VertexData>>();
	vertexBuffer_->CreateResource(6);
	vertexBuffer_->CreateVertexBufferView();

	materialBuffer_ = make_unique<BufferResource<MaterialDefferdShading>>();
	materialBuffer_->CreateResource();

	indexBuffer_ = make_unique<BufferResource<uint32_t>>();
	indexBuffer_->CreateResource(6);
	indexBuffer_->CreateIndexBufferView();

	wvp_ = make_unique<BufferResource<TransformationMatrix>>();
	wvp_->CreateResource();

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
	//PostDepthDraw();

	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	D3D12_RESOURCE_BARRIER barrier{};
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	//barrier.Transition.Subresource = 0xFFFFFFFF;
	barrier.Transition.pResource = colorTexBuffer_->GetBuffer();
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
	DirectXCommon::GetInstance()->GetCommands().m_pList->ResourceBarrier(1, &barrier);


}

void DefferredShading::PreNormalDraw()
{
	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	// レンダーターゲットをセット
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = RTVDescriptorManager::GetHandle(normalTexBuffer_->GetRtvIndex());
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = DSVDescriptorManager::GetHandle(depthBuffer_->GetDsvIndex());
	D3D12_RESOURCE_BARRIER barrier{};
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource = normalTexBuffer_->GetBuffer();
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

void DefferredShading::PostNormalDraw()
{
	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	D3D12_RESOURCE_BARRIER barrier{};
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	//barrier.Transition.Subresource = 0xFFFFFFFF;
	barrier.Transition.pResource = normalTexBuffer_->GetBuffer();
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
	DirectXCommon::GetInstance()->GetCommands().m_pList->ResourceBarrier(1, &barrier);
}

void DefferredShading::PrePosDraw()
{
	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	// レンダーターゲットをセット
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = RTVDescriptorManager::GetHandle(PosTexBuffer_->GetRtvIndex());
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = DSVDescriptorManager::GetHandle(depthBuffer_->GetDsvIndex());
	D3D12_RESOURCE_BARRIER barrier{};
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource = PosTexBuffer_->GetBuffer();;
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

void DefferredShading::Draw( const CameraData& camera)
{
	ColorBufferUpdate();
	ComPtr<ID3D12GraphicsCommandList> m_pList = DirectXCommon::GetInstance()->GetCommands().m_pList;
	SPSOProperty PSO = GraphicsPipelineManager::GetInstance()->GetPso().ColorPostProcess;

    m_pList->SetGraphicsRootSignature(PSO.rootSignature.Get());
	m_pList->SetPipelineState(PSO.GraphicsPipelineState.Get());

	vertexBuffer_->CommandVertexBufferViewCall();
	vertexBuffer_->CommandPrimitiveTopologyCall();
	indexBuffer_->CommandIndexBufferViewCall();

	wvp_->CommandCall(0);
	materialBuffer_->CommandCall(1);
	DescriptorManager::rootParamerterCommand(2, colorTexBuffer_->GetSrvIndex());
	DescriptorManager::rootParamerterCommand(3, normalTexBuffer_->GetSrvIndex());
	DescriptorManager::rootParamerterCommand(4, PosTexBuffer_->GetSrvIndex());
	DescriptorManager::rootParamerterCommand(5, depthTexBuffer_->GetSrvIndex());
	camera.buffer_->CommandCall(6);
	camera.buffer_->CommandCall(7);

	DescriptorManager::rootParamerterCommand(8, LightingManager::dsvHandle());
	m_pList->SetGraphicsRootConstantBufferView(9, LightingManager::GetBuffer()->GetGPUVirtualAddress());
	DirectionalLight::CommandCall(10);

	m_pList->DrawInstanced(6, 1, 0, 0);
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

	PosTexBuffer_ = make_unique<BufferResource<uint32_t>>();
	PosTexBuffer_->CreateResource(format, WinApp::GetkCilientWidth(), WinApp::GetkCilientHeight());
	PosTexBuffer_->TransfarImage(pixCount,rowPitch,depthPitch);
	PosTexBuffer_->RegisterSRV(format,"DeferredShadingPos");
	PosTexBuffer_->RegisterRTV(format, "DeferredShadingPos");

	//深度
	depthBuffer_ = make_unique<BufferResource<uint32_t>>();
	D3D12_RESOURCE_DESC resourceDesc = {};
	resourceDesc.Width = WinApp::GetkCilientWidth();
	resourceDesc.Height = WinApp::GetkCilientHeight();
	resourceDesc.MipLevels = 1;
	resourceDesc.DepthOrArraySize = 1;

	resourceDesc.Format = DXGI_FORMAT_D32_FLOAT;
	resourceDesc.SampleDesc.Count = 1;
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	D3D12_HEAP_PROPERTIES heapProperties{};
	heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;

	D3D12_CLEAR_VALUE depthClearValue{};
	depthClearValue.DepthStencil.Depth = 1.0f;
	depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;

	depthBuffer_->CreateResource(resourceDesc,heapProperties, D3D12_RESOURCE_STATE_DEPTH_WRITE, depthClearValue);
	depthBuffer_->RegisterDSV(DXGI_FORMAT_D32_FLOAT, "DeferredShadingDepth");

	depthTexBuffer_ = make_unique<BufferResource<uint32_t>>();

	//resourceDesc設定
	D3D12_RESOURCE_DESC resourceTexDesc = {};
	resourceTexDesc.Width = WinApp::GetkCilientWidth();
	resourceTexDesc.Height = WinApp::GetkCilientHeight();
	resourceTexDesc.MipLevels = 1;
	resourceTexDesc.DepthOrArraySize = 1;
	resourceTexDesc.Format = DXGI_FORMAT_D32_FLOAT;
	resourceTexDesc.SampleDesc.Count = 1;
	resourceTexDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resourceTexDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
	//Heap設定
	D3D12_HEAP_PROPERTIES heapPram{};
	heapPram.Type = D3D12_HEAP_TYPE_DEFAULT;
	D3D12_CLEAR_VALUE color = {};
	color.Format = DXGI_FORMAT_D32_FLOAT;
	color.DepthStencil.Depth = 1.0f;
	color.DepthStencil.Stencil = 0;
	depthTexBuffer_->CreateResource(resourceTexDesc,heapPram,D3D12_RESOURCE_STATE_GENERIC_READ,color);
	depthTexBuffer_->RegisterSRV(DXGI_FORMAT_R32_FLOAT, "DeferredShadingDepthTex");
	depthTexBuffer_->RegisterDSV(DXGI_FORMAT_D32_FLOAT, "DeferredShadingDepthTex");



}

void DefferredShading::PostPosDraw()
{

	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	D3D12_RESOURCE_BARRIER barrier{};
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	//barrier.Transition.Subresource = 0xFFFFFFFF;
	barrier.Transition.pResource = PosTexBuffer_->GetBuffer();
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
	DirectXCommon::GetInstance()->GetCommands().m_pList->ResourceBarrier(1, &barrier);


}

void DefferredShading::PreDepthDraw()
{
	////shadowMapTest用
	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	D3D12_CPU_DESCRIPTOR_HANDLE dsvShadowHandle = DSVDescriptorManager::GetHandle(depthTexBuffer_->GetDsvIndex());

	D3D12_RESOURCE_BARRIER barrier;
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	// 全てのサブリソースを選択
	barrier.Transition.Subresource = 0xFFFFFFFF;
	barrier.Transition.pResource = depthTexBuffer_->GetBuffer();
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_GENERIC_READ;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_DEPTH_WRITE;
	commands.m_pList->ResourceBarrier(1, &barrier);

	commands.m_pList->OMSetRenderTargets(0, nullptr, false, &dsvShadowHandle);

	CommandCallView(static_cast<float>(WinApp::GetkCilientWidth()), static_cast<float>(WinApp::GetkCilientHeight()));
	CommandCallScissor();

	commands.m_pList->ClearDepthStencilView(dsvShadowHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

}

void DefferredShading::PostDepthDraw()
{
	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	D3D12_RESOURCE_BARRIER barrier;
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	// 全てのサブリソースを選択
	barrier.Transition.Subresource = 0xFFFFFFFF;
	barrier.Transition.pResource = depthTexBuffer_->GetBuffer();
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_DEPTH_WRITE;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_GENERIC_READ;
	DirectXCommon::GetInstance()->GetCommands().m_pList->ResourceBarrier(1, &barrier);
}


void DefferredShading::ColorBufferUpdate()
{
	Vector2 pos_ = {};
	Vector2 size_ = { static_cast<float>(WinApp::GetkCilientWidth()), static_cast<float>(WinApp::GetkCilientHeight()) };

	vector<VertexData>vertexMap = {};
	vertexMap.resize(6);
	vertexMap[0].position = { pos_.x, pos_.y + size_.y,0.0f, 1.0f }; // 左下
	vertexMap[0].texcoord = { 0.0f, 1.0f };
	vertexMap[1].position = { pos_.x, pos_.y, 0.0f, 1.0f }; // 左上
	vertexMap[1].texcoord = { 0.0f, 0.0f };
	vertexMap[2].position = { pos_.x + size_.x, pos_.y + size_.y, 0.0f,1.0f }; // 右下
	vertexMap[2].texcoord = { 1.0f,1.0f };
	vertexMap[3].position = { pos_.x, pos_.y, 0.0f, 1.0f }; // 左上
	vertexMap[3].texcoord = { 0.0f, 0.0f };
	vertexMap[4].position = { pos_.x + size_.x, pos_.y, 0.0f, 1.0f }; // 右上
	vertexMap[4].texcoord = { 1.0f, 0.0f };
	vertexMap[5].position = { pos_.x + size_.x, pos_.y + size_.y, 0.0f,1.0f }; // 右下
	vertexMap[5].texcoord = { 1.0f,1.0f };

	indexData_.resize(6);
	indexData_[0] = 0; indexData_[1] = 1; indexData_[2] = 2;
	indexData_[3] = 1; indexData_[4] = 3; indexData_[5] = 2;

	vertexBuffer_->Map();
	vertexBuffer_->Setbuffer(vertexMap);

	indexBuffer_->Map();
	indexBuffer_->Setbuffer(indexData_);
	indexBuffer_->UnMap();

	TransformationMatrix wvpMap = {};
	Matrix4x4 OrthographicMatrix = Math::Matrix::OrthographicMatrix(0, 0, float(WinApp::GetkCilientWidth()), float(WinApp::GetkCilientHeight()), 0.0f, 100.0f);
	wvpMap.world = Math::Matrix::Identity();
	wvpMap.WVP = OrthographicMatrix;

	wvp_->Map();
	wvp_->Setbuffer(wvpMap);
	wvp_->UnMap();

	materialData.color = { 1,1,1,1 };
	ImGui::DragFloat("s", &materialData.shininess,-1.0f,1.0);
	materialBuffer_->Map();
	materialBuffer_->Setbuffer(materialData);
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