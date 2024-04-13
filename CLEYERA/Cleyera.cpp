#include "Cleyera.h"

Cleyera* Cleyera::GetInstance()
{
	static Cleyera instance;
	return &instance;
}

void Cleyera::Initialize()
{
	Cleyera::GetInstance();

	WinApp::Initialize();
	DirectXCommon::initialize();
	DescriptorManager::Initialize();
	RTVDescriptorManager::Initialize();
	ShaderManager::Initialize();
	GraphicsPipelineManager::Initialize();
	TextureManager::Initialize();
	ImGuiManager::Initialize();
	Input::Initialize();

	AudioManager::Initialize();
	LightingManager::Initialize();
	DirectionalLight::Initialize();

	GlobalVariables::GetInstance()->LoadFiles();
}

void Cleyera::Finalize()
{
	ModelManager::Finalize();
	AudioManager::Finalize();
	TextureManager::Finalize();
	DescriptorManager::Clear();
	ImGuiManager::Finalize();
	DirectXCommon::Finalize();
	WinApp::Finalize();
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
