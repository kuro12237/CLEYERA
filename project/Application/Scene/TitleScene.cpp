#include "TitleScene.h"

void TitleScene::Initialize()
{
	WinApp::GetInstance()->SetTiTleName(L"GunHead");
	PostEffect::GetInstance()->Initialize();
	ChangeSceneAnimation::GetInstance()->Initialize();
	camera_.Initialize();

	camera_.UpdateMatrix();
	CameraManager::GetInstance()->ResetCamera(camera_);
}

void TitleScene::Update([[maybe_unused]] GameManager* Scene)
{
#ifdef _USE_IMGUI

	ImGui::Begin("TitleScene");
	ImGui::Text("A:PUSH SelectScene");
	ImGui::End();

#endif // _USE_IMGUI

	ChangeSceneAnimation::GetInstance()->Update();

	if (Input::PushBottonPressed(XINPUT_GAMEPAD_A))
	{
		ChangeSceneAnimation::GetInstance()->ChangeStart();
	}

	camera_.UpdateMatrix();
	PostEffect::GetInstance()->Update();

	if (ChangeSceneAnimation::GetInstance()->GetIsChangeSceneFlag())
	{
		Scene->ChangeState(new GameScene);
		return;
	}
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
	ChangeSceneAnimation::GetInstance()->Draw();

}
