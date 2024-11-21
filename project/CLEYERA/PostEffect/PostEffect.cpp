#include "PostEffect.h"

using namespace Engine::Base::DX;

using namespace Engine::Base::Win;
using namespace Engine::Buffer;
using namespace Engine::Manager;
using namespace Engine::Light;
using namespace Engine;

PostEffect* PostEffect::GetInstance()
{
	static PostEffect instatnce;
	return &instatnce;
}

void PostEffect::Initialize()
{
	if (isInitialize_)
	{
		return;
	}
	isInitialize_ = true;

	DXGI_FORMAT texBufFormat = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	const UINT pixCount = WinApp::GetkCilientWidth() * WinApp::GetkCilientHeight();
	const UINT rowPitch = sizeof(UINT) * WinApp::GetkCilientWidth();
	const UINT depthPitch = rowPitch * WinApp::GetkCilientHeight();

	texBuf_ = make_unique<BufferResource<uint32_t>>();
	texBuf_->CreateResource(texBufFormat, WinApp::GetkCilientWidth(), WinApp::GetkCilientHeight());
	texBuf_->TransfarImage(pixCount,rowPitch,depthPitch);
	texBuf_->RegisterRTV(texBufFormat , "texBuf");
	texBuf_->RegisterSRV(texBufFormat , "texBuf");

	DXGI_FORMAT albed = DXGI_FORMAT_R8G8B8A8_UNORM;
	albedBuf_ = make_unique<BufferResource<uint32_t>>();
	albedBuf_->CreateResource(albed, WinApp::GetkCilientWidth(), WinApp::GetkCilientHeight());
	albedBuf_->TransfarImage(pixCount, rowPitch, depthPitch);
	albedBuf_->RegisterRTV(albed, "albedBuf");
	albedBuf_->RegisterSRV(albed, "albedBuf");


	DXGI_FORMAT outline = DXGI_FORMAT_R8G8B8A8_UNORM;
	outLineColor_ = make_unique<BufferResource<uint32_t>>();
	outLineColor_->CreateResource(outline, WinApp::GetkCilientWidth(), WinApp::GetkCilientHeight());
	outLineColor_->TransfarImage(pixCount, rowPitch, depthPitch);
	outLineColor_->RegisterRTV(outline, "oullineBuf");
	outLineColor_->RegisterSRV(outline, "oullineBuf");

	//resourceDesc設定
	D3D12_RESOURCE_DESC resourceTexDesc = {};
	resourceTexDesc.Width = WinApp::GetkCilientWidth();
	resourceTexDesc.Height = WinApp::GetkCilientHeight();
	resourceTexDesc.MipLevels = 1;
	resourceTexDesc.DepthOrArraySize = 1;
	resourceTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	resourceTexDesc.SampleDesc.Count = 1;
	resourceTexDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resourceTexDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
	//Heap設定
	D3D12_HEAP_PROPERTIES heapPram{};
	heapPram.Type = D3D12_HEAP_TYPE_DEFAULT;
	D3D12_CLEAR_VALUE color = {};
	color.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	color.DepthStencil.Depth = 1.0f;
	color.DepthStencil.Stencil = 0;

	depthTexBuffer_ = make_unique<BufferResource<uint32_t>>();
	depthTexBuffer_->CreateResource(resourceTexDesc, heapPram, D3D12_RESOURCE_STATE_GENERIC_READ, color);
	depthTexBuffer_->RegisterSRV(DXGI_FORMAT_R24_UNORM_X8_TYPELESS, "PostEffectDepthTex");
	depthTexBuffer_->RegisterDSV(DXGI_FORMAT_D24_UNORM_S8_UINT, "PostEffectDepthTex");

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

void PostEffect::Draw()
{
	Commands commands = DirectXCommon::GetInstance()->GetCommands();

	SPSOProperty PSO = {};
	PSO = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::POST_EFFECT, "None");

	commands.m_pList->SetGraphicsRootSignature(PSO.rootSignature.Get());
	commands.m_pList->SetPipelineState(PSO.GraphicsPipelineState.Get());

	commands.m_pList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//matrix0
	wvp_->CommandCall(0);
	paramBuffer_->CommandCall(1);

	//tex1
	DescriptorManager::rootParamerterCommand(2, texBuf_->GetSrvIndex());
	//影用
	DescriptorManager::rootParamerterCommand(3, depthTexBuffer_->GetSrvIndex());

	//ブラー用
	blurParamBuffer_->CommandCall(4);
	//色調整
	adjustedColorBuffer_->CommandCall(5);
	//平行光源
	DirectionalLight::CommandCall(6);

	DirectionalLight::CommandCall(7);
	//view
	CameraManager::GetInstance()->PsCommandCall(8);
	CameraManager::GetInstance()->VsCommandCall(9);

	DescriptorManager::rootParamerterCommand(10, albedBuf_->GetSrvIndex());

	commands.m_pList->DrawInstanced(6, 1, 0, 0);
}

void PostEffect::PreDraw()
{
	//barriri
	Commands commands = DirectXCommon::GetInstance()->GetCommands();

	// レンダーターゲットをセット
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = RTVDescriptorManager::GetHandle(texBuf_->GetRtvIndex());
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = DSVDescriptorManager::GetHandle(depthTexBuffer_->GetDsvIndex());
	D3D12_CPU_DESCRIPTOR_HANDLE rtvColorHandle = RTVDescriptorManager::GetHandle(albedBuf_->GetRtvIndex());

	D3D12_RESOURCE_BARRIER barrier[3]{};
	barrier[0].Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier[0].Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier[0].Transition.pResource = texBuf_->GetBuffer();
	barrier[0].Transition.StateBefore = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
	barrier[0].Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;

	barrier[1].Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier[1].Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier[1].Transition.pResource = albedBuf_->GetBuffer();
	barrier[1].Transition.StateBefore = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
	barrier[1].Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
	//深度
	barrier[2].Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier[2].Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier[2].Transition.Subresource = 0xFFFFFFFF;
	barrier[2].Transition.pResource = depthTexBuffer_->GetBuffer();
	barrier[2].Transition.StateBefore = D3D12_RESOURCE_STATE_GENERIC_READ;
	barrier[2].Transition.StateAfter = D3D12_RESOURCE_STATE_DEPTH_WRITE;

	commands.m_pList->ResourceBarrier(3, barrier);

	//commands.m_pList->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[] = { rtvHandle,rtvColorHandle };
	commands.m_pList->OMSetRenderTargets(_countof(rtvHandles), rtvHandles, false, &dsvHandle);
	CommandCallView(static_cast<float>(WinApp::GetkCilientWidth()), static_cast<float>(WinApp::GetkCilientHeight()));
	CommandCallScissor();

	commands.m_pList->ClearRenderTargetView(rtvHandle, clearColor,0, nullptr);
	commands.m_pList->ClearRenderTargetView(rtvColorHandle, clearColor, 0, nullptr);

	commands.m_pList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

}

void PostEffect::PostDraw()
{
	Commands commands = DirectXCommon::GetInstance()->GetCommands();

	D3D12_RESOURCE_BARRIER barrier[3]{};
	barrier[0].Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier[0].Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier[0].Transition.Subresource = 0xFFFFFFFF;
	barrier[0].Transition.pResource = texBuf_->GetBuffer();
	barrier[0].Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	barrier[0].Transition.StateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
	barrier[1].Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier[1].Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier[1].Transition.Subresource = 0xFFFFFFFF;
	barrier[1].Transition.pResource = albedBuf_->GetBuffer();
	barrier[1].Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	barrier[1].Transition.StateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
	//深度
	barrier[2].Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier[2].Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier[2].Transition.Subresource = 0xFFFFFFFF;
	barrier[2].Transition.pResource = depthTexBuffer_->GetBuffer();
	barrier[2].Transition.StateBefore = D3D12_RESOURCE_STATE_DEPTH_WRITE;
	barrier[2].Transition.StateAfter = D3D12_RESOURCE_STATE_GENERIC_READ;

	commands.m_pList->ResourceBarrier(3, barrier);
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
	if (s == VIGNETTE)
	{
		adjustedColorParam_.vignetteFlag = flag;
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
