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
	DirectXCommon::initialize();
	DescriptorManager::Initialize();
	RTVDescriptorManager::Initialize();
	ShaderManager::Initialize();
	GraphicsPipelineManager::Initialize();
	TextureManager::Initialize();
	ImGuiManager::Initialize();
	Input::Initialize();

	AudioManager::GetInstance()->Initialize();
	LightingManager::Initialize();
	DirectionalLight::Initialize();

	GlobalVariables::GetInstance()->LoadFiles();
}

void Cleyera::Finalize()
{
	ModelManager::Finalize();
	AudioManager::GetInstance()->Finalize();
	TextureManager::Finalize();
	DescriptorManager::Clear();
	ImGuiManager::Finalize();
	DirectXCommon::Finalize();
	WinApp::GetInstance()->Finalize();
}

void Cleyera::BeginFlame()
{
	ImGuiManager::BeginFlame();
	Input::BeginFlame();

	DescriptorManager::BeginFlame();
	DSVDescriptorManager::BeginFlame();
	RTVDescriptorManager::BeginFlame();
}

void Cleyera::EndFlame()
{
	ImGuiManager::EndFlame();
}
