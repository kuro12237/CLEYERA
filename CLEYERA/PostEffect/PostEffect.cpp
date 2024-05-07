#include "PostEffect.h"

PostEffect* PostEffect::GetInstance()
{
	static PostEffect instatnce;
	return &instatnce;
}

void PostEffect::Initialize(const string& name)
{
	if (PostEffectManager::GetInstance()->CheckData(name))
	{
		CreateTexBuffer(texBuffer_,srvIndex_);
		CreateTexBuffer(colorBuffer_, colorSrvIndex_);
		CreateRTV(texBuffer_,rtvIndex_);
		CreateRTV(colorBuffer_, colorRtvIndex_);
		CreateDSV();
		SPostEffectData p;
		p.name = name;
		p.depthBuffer_ = depthBuffer_;
		p.resource = texBuffer_;
		p.rtvIndex = rtvIndex_;
		p.dsvindex = dsvIndex_;
		p.srvIndex = srvIndex_;
		PostEffectManager::GetInstance()->SetData(name, p);
	}
	else
	{
		SPostEffectData data = PostEffectManager::GetInstance()->GetData(name);
		rtvIndex_ = data.rtvIndex;
		srvIndex_ = data.srvIndex;
		dsvIndex_ = data.dsvindex;
		texBuffer_ = data.resource;
		depthBuffer_ = data.depthBuffer_;
	}


	if (PostEffectManager::GetInstance()->CheckData(name + "shadow"))
	{
		CreateShadowMap();
		SPostEffectData p;
		p.name = name + "shadow";
		p.resource = depthNormalBuffer_;
		p.rtvIndex = rtvshadowIndex_;
		p.srvIndex = srvShadowIndex_;
		p.dsvindex = dsvShadowIndex_;
		PostEffectManager::GetInstance()->SetData(name + "shadow", p);
	}
	else
	{
		SPostEffectData data = PostEffectManager::GetInstance()->GetData(name + "shadow");
		rtvshadowIndex_ = data.rtvIndex;
		srvShadowIndex_ = data.srvIndex;
		dsvShadowIndex_ = data.dsvindex;
		depthNormalBuffer_ = data.resource;
	}

	//CreateBloom();

	wvp_ = std::make_unique<BufferResource<TransformationMatrix>>();
	wvp_->CreateResource(1);

	paramBuffer_ = std::make_unique<BufferResource<PostEffectParam>>();
	paramBuffer_->CreateResource(1);
	param_.uvMatrix = Math::Matrix::Identity();

	blurParamBuffer_ = make_unique<BufferResource<PostEffectBlurParam>>();
	blurParamBuffer_->CreateResource(1);

	adjustedColorBuffer_ = make_unique<BufferResource<PostEffectAdjustedColorParam>>();
	adjustedColorBuffer_->CreateResource(1);
}

void PostEffect::Update()
{

	TransformationMatrix wvpMap = {};
	Math::Matrix::Matrix4x4 OrthographicMatrix = Math::Matrix::OrthographicMatrix(0, 0, float(WinApp::GetkCilientWidth()), float(WinApp::GetkCilientHeight()), 0.0f, 100.0f);
	wvpMap.world = Math::Matrix::Identity();
	wvpMap.WVP = OrthographicMatrix;

	wvp_->Map();
	wvp_->Setbuffer(wvpMap);
	wvp_->UnMap();

	paramBuffer_->Map();
	param_.texSize = size_;
	param_.uvMatrix = Math::Matrix::AffineMatrix(uvScale_, uvRotate_, uvTranslate_);
	paramBuffer_->Setbuffer(param_);
	paramBuffer_->UnMap();

	blurParamBuffer_->Map();
	blurParamBuffer_->Setbuffer(blurParam_);
	blurParamBuffer_->UnMap();

	adjustedColorBuffer_->Map();
	adjustedColorBuffer_->Setbuffer(adjustedColorParam_);
	adjustedColorBuffer_->UnMap();
}

void PostEffect::Draw(const CameraData& view)
{
	Commands commands = DirectXCommon::GetInstance()->GetCommands();

	SPSOProperty PSO = {};
	PSO = GraphicsPipelineManager::GetInstance()->GetPso().PostEffectTest;

	commands.m_pList->SetGraphicsRootSignature(PSO.rootSignature.Get());
	commands.m_pList->SetPipelineState(PSO.GraphicsPipelineState.Get());

	commands.m_pList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//matrix0
	wvp_->CommandCall(0);
	paramBuffer_->CommandCall(1);

	//tex1
	DescriptorManager::rootParamerterCommand(2, srvIndex_);
	//影用
	DescriptorManager::rootParamerterCommand(3, srvShadowIndex_);

	//ブラー用
	blurParamBuffer_->CommandCall(4);
	//色調整
	adjustedColorBuffer_->CommandCall(5);
	//平行光源
	DirectionalLight::CommandCall(6);

	DirectionalLight::CommandCall(7);
	//view
	view.buffer_->CommandCall(8);
	view.buffer_->CommandCall(9);
	DescriptorManager::rootParamerterCommand(10, colorSrvIndex_);

	commands.m_pList->DrawInstanced(6, 1, 0, 0);
}

void PostEffect::PreDraw()
{
	//barriri
	Commands commands = DirectXCommon::GetInstance()->GetCommands();


	// レンダーターゲットをセット
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = RTVDescriptorManager::GetHandle(rtvIndex_);
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = DSVDescriptorManager::GetHandle(dsvIndex_);
	D3D12_CPU_DESCRIPTOR_HANDLE rtvColorHandle= RTVDescriptorManager::GetHandle(colorRtvIndex_);

	D3D12_RESOURCE_BARRIER barrier[2]{};
	barrier[0].Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier[0].Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier[0].Transition.pResource = texBuffer_.Get();
	barrier[0].Transition.StateBefore = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
	barrier[0].Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;

	barrier[1].Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier[1].Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier[1].Transition.pResource = colorBuffer_.Get();
	barrier[1].Transition.StateBefore = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
	barrier[1].Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
	commands.m_pList->ResourceBarrier(2, barrier);

	//commands.m_pList->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[] = { rtvHandle,rtvColorHandle };
	commands.m_pList->OMSetRenderTargets(2, rtvHandles, false, &dsvHandle);
	CommandCallView(static_cast<float>(WinApp::GetkCilientWidth()), static_cast<float>(WinApp::GetkCilientHeight()));
	CommandCallScissor();

	commands.m_pList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
	commands.m_pList->ClearRenderTargetView(rtvColorHandle, clearColor, 0, nullptr);

	commands.m_pList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

}

void PostEffect::PostDraw()
{
	D3D12_RESOURCE_BARRIER barrier[2]{};
	barrier[0].Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier[0].Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier[0].Transition.Subresource = 0xFFFFFFFF;
	barrier[0].Transition.pResource = texBuffer_.Get();
	barrier[0].Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	barrier[0].Transition.StateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
	barrier[1].Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier[1].Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier[1].Transition.Subresource = 0xFFFFFFFF;
	barrier[1].Transition.pResource = colorBuffer_.Get();
	barrier[1].Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	barrier[1].Transition.StateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
	DirectXCommon::GetInstance()->GetCommands().m_pList->ResourceBarrier(2, barrier);
}

void PostEffect::SetSelectPostEffect(SelectPostEffect s, bool flag)
{
	if (s == GRAYSCALE)
	{
		adjustedColorParam_.grayScaleFlag = flag;
	}
	if (s == INVERT)
	{
		adjustedColorParam_.InvertFlag = flag;
	}
	if (s == BRINGHTNESS)
	{
		adjustedColorParam_.BringhtnessFlag = flag;
	}
	if (s == CONTRAST)
	{
		adjustedColorParam_.ContrastFlag = flag;
	}
	if (s == HUE)
	{
		adjustedColorParam_.HueFlag = flag;
	}

	if (s == AVERAGE_BLUR)
	{
		blurParam_.UseFlag = flag;
	}
}

void PostEffect::CommandCallView(const float& width, const float& height)
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

void PostEffect::CommandCallScissor()
{
	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	D3D12_RECT scissorRect{};
	scissorRect.left = 0;
	scissorRect.right = (WinApp::GetkCilientWidth());
	scissorRect.top = 0;
	scissorRect.bottom = WinApp::GetkCilientHeight();

	commands.m_pList->RSSetScissorRects(1, &scissorRect);
}

void PostEffect::CreateTexBuffer(ComPtr<ID3D12Resource>&buf,uint32_t &index)
{
	ComPtr<ID3D12Device> device = DirectXCommon::GetInstance()->GetDevice();

	//resourceDesc設定
	D3D12_RESOURCE_DESC resourceDesc = {};
	resourceDesc.Width = WinApp::GetkCilientWidth();
	resourceDesc.Height = WinApp::GetkCilientHeight();
	resourceDesc.MipLevels = 1;
	resourceDesc.DepthOrArraySize = 1;
	resourceDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
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
	//float colorData[] = { 0.0f,0.0f,0.0f,1.0f };
	color.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	for (uint32_t i = 0; i < 4; i++)
	{
		color.Color[i] = clearColor[i];
	}

	//resource作成
	HRESULT hr = {};
	hr =
		device->CreateCommittedResource(
			&heapPram,
			D3D12_HEAP_FLAG_NONE,
			&resourceDesc,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
			&color,
			IID_PPV_ARGS(&buf)
		);
	TransfarImage(buf);
	index = AddSRVDescripter(buf);
}

void PostEffect::TransfarImage(ComPtr<ID3D12Resource>&buf)
{
	const UINT pixCount = WinApp::GetkCilientWidth() * WinApp::GetkCilientHeight();

	const UINT rowPitch = sizeof(UINT) * WinApp::GetkCilientWidth();

	const UINT depthPitch = rowPitch * WinApp::GetkCilientHeight();

	UINT* img = new UINT[pixCount];
	for (int i = 0; i < int(pixCount); i++)
	{
		img[i] = 0xff0000ff;
	}
	HRESULT hr = {};
	hr = buf->WriteToSubresource(
		0,
		nullptr,
		img,
		rowPitch,
		depthPitch
	);
	assert(SUCCEEDED(hr));
	delete[] img;

}

uint32_t PostEffect::AddSRVDescripter(ComPtr<ID3D12Resource>&buf)
{
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = { };
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	//Despcripter
	DescriptorManager::IndexIncrement("postEffect");
	uint32_t index = DescriptorManager::GetIndex();
	DescriptorManager::SetCPUDescripterHandle(
		DescriptorManager::GetCPUDescriptorHandle(
			DirectXCommon::GetInstance()->GetSrvHeap(),
			index),
		index
	);

	DescriptorManager::SetGPUDescripterHandle(
		DescriptorManager::GetGPUDescriptorHandle(
			DirectXCommon::GetInstance()->GetSrvHeap(),
			index),
		index
	);

	DescriptorManager::CGHandlePtr();
	DescriptorManager::CreateShaderResourceView(
		buf.Get(),
		srvDesc,
		index);

	return index;
}

void PostEffect::CreateRTV(ComPtr<ID3D12Resource>&buf,uint32_t &rtvIndex)
{
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	RTVDescriptorManager::IndexIncrement("postEffect");
	rtvIndex = RTVDescriptorManager::GetIndex();
	RTVDescriptorManager::AddPointer(buf, rtvDesc);

	D3D12_RENDER_TARGET_VIEW_DESC rtvColorDesc{};
	rtvColorDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	rtvColorDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	RTVDescriptorManager::IndexIncrement("postEffectColor");
	rtvIndex = RTVDescriptorManager::GetIndex();
	RTVDescriptorManager::AddPointer(buf, rtvDesc);
}

void PostEffect::CreateDSV()
{
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

	HRESULT hr = {};
	//作成
	hr = DirectXCommon::GetInstance()->GetDevice()->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&depthClearValue,
		IID_PPV_ARGS(&depthBuffer_)
	);
	assert(SUCCEEDED(hr));

	D3D12_DEPTH_STENCIL_VIEW_DESC desc{};
	desc.Format = DXGI_FORMAT_D32_FLOAT;
	desc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;

	DSVDescriptorManager::IndexIncrement("posteffect");
	dsvIndex_ = DSVDescriptorManager::GetIndex();
	DSVDescriptorManager::AddPointer(depthBuffer_, desc);

}

void PostEffect::CreateShadowMap()
{

	CreateShadowMapResource();
	CreateShadowMapDSV();
	CreateShadowMapSRV();


}

void PostEffect::CreateShadowMapResource()
{
	ComPtr<ID3D12Device> device = DirectXCommon::GetInstance()->GetDevice();
	HRESULT hr;

	//resourceDesc設定
	D3D12_RESOURCE_DESC resourceDesc = {};
	resourceDesc.Width = WinApp::GetkCilientWidth();
	resourceDesc.Height = WinApp::GetkCilientHeight();
	resourceDesc.MipLevels = 1;
	resourceDesc.DepthOrArraySize = 1;
	resourceDesc.Format = DXGI_FORMAT_D32_FLOAT;
	resourceDesc.SampleDesc.Count = 1;
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
	//Heap設定
	D3D12_HEAP_PROPERTIES heapPram{};
	heapPram.Type = D3D12_HEAP_TYPE_DEFAULT;
	//色
	D3D12_CLEAR_VALUE color = {};
	color.Format = DXGI_FORMAT_D32_FLOAT;
	color.DepthStencil.Depth = 1.0f;
	color.DepthStencil.Stencil = 0;

	//resource作成
	hr =
		device->CreateCommittedResource(
			&heapPram,
			D3D12_HEAP_FLAG_NONE,
			&resourceDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			&color,
			IID_PPV_ARGS(&depthNormalBuffer_)
		);
}

void PostEffect::CreateShadowMapDSV()
{
	D3D12_DEPTH_STENCIL_VIEW_DESC desc{};
	desc.Format = DXGI_FORMAT_D32_FLOAT;
	desc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	desc.Flags = D3D12_DSV_FLAG_NONE;

	DSVDescriptorManager::IndexIncrement("shadow");
	dsvShadowIndex_ = DSVDescriptorManager::GetIndex();
	DSVDescriptorManager::AddPointer(depthNormalBuffer_.Get(), desc);
}

void PostEffect::CreateShadowMapSRV()
{
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = { };
	srvDesc.Format = DXGI_FORMAT_R32_FLOAT;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;
	srvDesc.Texture2D.PlaneSlice = 0;
	srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;

	//Despcripter
	DescriptorManager::IndexIncrement("shadow");
	uint32_t srvIndex = DescriptorManager::GetIndex();
	DescriptorManager::SetCPUDescripterHandle(
		DescriptorManager::GetCPUDescriptorHandle(
			DirectXCommon::GetInstance()->GetSrvHeap(),
			srvIndex),
		srvIndex
	);

	DescriptorManager::SetGPUDescripterHandle(
		DescriptorManager::GetGPUDescriptorHandle(
			DirectXCommon::GetInstance()->GetSrvHeap(),
			srvIndex),
		srvIndex
	);

	DescriptorManager::CGHandlePtr();
	DescriptorManager::CreateShaderResourceView(
		depthNormalBuffer_.Get(),
		srvDesc,
		srvIndex);
	srvShadowIndex_ = srvIndex;
}

void PostEffect::CreateBloom()
{
	CreateBloomBuffer();
	CreateBloomRTV();
	CreateBloomSRV();
}

void PostEffect::CreateBloomBuffer()
{
	ComPtr<ID3D12Device> device = DirectXCommon::GetInstance()->GetDevice();

	for (uint32_t i = 0; i < BloomNum_; i++)
	{
		//resourceDesc設定
		D3D12_RESOURCE_DESC resourceDesc = {};
		resourceDesc.Width = WinApp::GetkCilientWidth();
		resourceDesc.Height = WinApp::GetkCilientHeight();
		resourceDesc.MipLevels = 1;
		resourceDesc.DepthOrArraySize = 1;
		resourceDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
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
		//float colorData[] = { 0.0f,0.0f,0.0f,1.0f };
		color.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		for (uint32_t i = 0; i < 4; i++)
		{
			color.Color[i] = clearColor[i];
		}
		//resource作成
		HRESULT hr = {};
		hr =
			device->CreateCommittedResource(
				&heapPram,
				D3D12_HEAP_FLAG_NONE,
				&resourceDesc,
				D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
				&color,
				IID_PPV_ARGS(&BloomBuffer_[i])
			);

		TransfarImage(BloomBuffer_[i]);
		AddSRVDescripter(BloomBuffer_[i]);
	}

}

void PostEffect::CreateBloomRTV()
{
}

void PostEffect::CreateBloomSRV()
{
}
