#include "TitleScene.h"

void TitleScene::Initialize()
{
	WinApp::GetInstance()->SetTiTleName(L"GunHead");
	PostEffect::GetInstance()->Initialize();
}

void TitleScene::Update([[maybe_unused]] GameManager* Scene)
{
#ifdef _USE_IMGUI

	ImGui::Begin("TitleScene");
	ImGui::Text("A:PUSH SelectScene");
	ImGui::End();

#endif // _USE_IMGUI


	if (Input::PushBottonPressed(XINPUT_GAMEPAD_A))
	{
		Scene->ChangeState(new GameScene);
		return;
	}
	PostEffect::GetInstance()->Update();
}

void TitleScene::PostProcessDraw()
{
	PostEffect::GetInstance()->PreDraw();
	PostEffect::GetInstance()->PostDraw();
}

void TitleScene::Back2dSpriteDraw()
{
}

void TitleScene::Object3dDraw()
{
}

void TitleScene::Flont2dSpriteDraw()
{
}
