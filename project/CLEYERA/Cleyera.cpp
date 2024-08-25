#include "Cleyera.h"

Cleyera* Cleyera::GetInstance()
{
	static Cleyera instance;
	return &instance;
}

void Cleyera::Initialize()
{
	Cleyera::GetInstance();

	WinApp::GetInstance()->Initialize();
	DirectXCommon::GetInstance()->initialize();
	DescriptorManager::Initialize();
	RTVDescriptorManager::Initialize();
	ShaderManager::Initialize();
	GraphicsPipelineManager::GetInstance()->Initialize();
	TextureManager::Initialize();
	ImGuiManager::Initialize();
	Input::Initialize();

	AudioManager::GetInstance()->Initialize();
	LightingManager::GetInstance()->Initialize();
	DirectionalLight::Initialize();

	GlobalVariables::GetInstance()->LoadFiles();
	CameraManager::GetInstance()->Initialize();
	RunTimeCounter::GetInstance()->Create();
	NoiseTexture::GetInstance()->Initialize();
	SkyBox::GetInstance()->Initialize();
	PostEffect::GetInstance()->Initialize();

}

void Cleyera::Finalize()
{
	ModelManager::Finalize();
	AudioManager::GetInstance()->Finalize();
	TextureManager::Finalize();
	DescriptorManager::Clear();
	ImGuiManager::Finalize();
	DirectXCommon::GetInstance()->Finalize();
	WinApp::GetInstance()->Finalize();
}

void Cleyera::BeginFlame()
{
	ImGuiManager::BeginFlame();
	Input::BeginFlame();

	DescriptorManager::BeginFlame();
	DSVDescriptorManager::BeginFlame();
	RTVDescriptorManager::BeginFlame();

	RunTimeCounter::GetInstance()->Update();
	SkyBox::GetInstance()->Update();

	ID3D12DescriptorHeap* heap[] = { DirectXCommon::GetInstance()->GetSrvHeap() };
	ComPtr<ID3D12GraphicsCommandList>commandList = DirectXCommon::GetInstance()->GetCommands().m_pList;
	commandList->SetDescriptorHeaps(1, heap);
}

void Cleyera::EndFlame()
{
	ImGuiManager::EndFlame();
}
