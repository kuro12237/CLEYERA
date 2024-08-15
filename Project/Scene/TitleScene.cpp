#include "TitleScene.h"

void TitleScene::Initialize()
{
	WinApp::GetInstance()->SetTiTleName(L"GunHead");
	PostEffect::GetInstance()->Initialize();
}

void TitleScene::Update(GameManager* Scene)
{

	if (Input::PushKeyPressed(DIK_G))
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
