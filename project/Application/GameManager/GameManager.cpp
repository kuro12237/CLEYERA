#include "GameManager.h"

using namespace Engine;
using namespace Engine::Base::Win;
using namespace Engine::Base::DX;
using namespace Engine::Manager;


GameManager::GameManager()
{
	Cleyera::Initialize();
	scene_ = make_unique<GameOverScene>();
	scene_->Initialize();
}

GameManager::~GameManager()
{
	Input::GetInstance()->VibrateController(0,0);

	Cleyera::Finalize();
}

void GameManager::Run()
{
	while (WinApp::GetInstance()->WinMsg())
	{
		Cleyera::BeginFlame();

#ifdef  _USE_IMGUI

		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.08f, 0.08f, 0.08f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.02f, 0.02f, 0.02f, 1.0f));
		ImGui::Begin("Debug");
	
		if (ImGui::BeginMenu("System"))
		{
			WinApp::GetInstance()->ImGuiUpdate();
			DirectXCommon::GetInstance()->ImGuiUpdate();
			if (ImGui::TreeNode("Descriptor"))
			{
				DSVDescriptorManager::ImGuiUpdate();
				RTVDescriptorManager::ImGuiUpdate();
				DescriptorManager::ImGuiUpdate();
				ImGui::TreePop();
			}
			ImGui::EndMenu();
		}

		SkyBox::GetInstance()->ImGuiUpdate();

		GlobalVariables::GetInstance()->Update();

#endif //  _USE_IMGUI

		LightingManager::ClearList();
		scene_->Update(this);

		PostEffect::GetInstance()->Update();
		DirectionalLight::Update();
		LightingManager::GetInstance()->TransfarBuffers();

#ifdef  _USE_IMGUI
		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
#endif // _USE_IMGUI

		PostEffect::GetInstance()->PreDraw();

		SkyBox::GetInstance()->Draw();
		scene_->PostProcessDraw();

		PostEffect::GetInstance()->PostDraw();

		DirectXCommon::GetInstance()->PreDraw();

		scene_->Back2dSpriteDraw();
		scene_->Object3dDraw();
		scene_->Flont2dSpriteDraw(); 
		
		Cleyera::EndFlame();
		DirectXCommon::GetInstance()->PostDraw();
	}
}

void GameManager::ChangeScene(unique_ptr<IScene> newScene)
{
	scene_ = move(newScene);

	scene_->Initialize();
	scene_->Update(this);

	return;
}
