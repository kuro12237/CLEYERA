#include "GameManager.h"

GameManager::GameManager()
{
	Cleyera::Initialize();

	Scene_ = new  TitleScene();
	Scene_->Initialize();
}

GameManager::~GameManager()
{
	delete Scene_;
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
		GlobalVariables::GetInstance()->Update();

#endif //  _USE_IMGUI

		LightingManager::ClearList();
		Scene_->Update(this);

		DirectionalLight::Update();
		LightingManager::GetInstance()->TransfarBuffers();

#ifdef  _USE_IMGUI
		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
#endif // _USE_IMGUI

		Scene_->PostProcessDraw();

		DirectXCommon::GetInstance()->PreDraw();

		Scene_->Back2dSpriteDraw();
		Scene_->Object3dDraw();
		Scene_->Flont2dSpriteDraw();

		Cleyera::EndFlame();
		DirectXCommon::GetInstance()->PostDraw();
	}
}

void GameManager::ChangeState(IScene* newScene)
{
	delete Scene_;

	Scene_ = move(newScene);

	Scene_->Initialize();
	Scene_->Update(this);

	return;
}
