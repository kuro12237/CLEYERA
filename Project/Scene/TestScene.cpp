#include "TestScene.h"

void TestScene::Initialize()
{
}

void TestScene::Update(GameManager* Scene)
{
	if (Input::PushKeyPressed(DIK_B))
	{
		Scene->ChangeState(new GameScene);
		return;
	}

}

void TestScene::PostProcessDraw()
{
}

void TestScene::Back2dSpriteDraw()
{
}

void TestScene::Object3dDraw()
{
}

void TestScene::Flont2dSpriteDraw()
{
}
