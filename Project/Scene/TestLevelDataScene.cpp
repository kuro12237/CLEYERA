#include "TestLevelDataScene.h"

void TestLevelDataScene::Initialize()
{
	postEffect_ = make_unique<PostEffect>();
	postEffect_->Initialize("testScene");
	camera_.Initialize();
	camera_.translation_.z = -16.0f;
	testObj_ = make_unique<testObject>();
	testObj_->Initialize();
}

void TestLevelDataScene::Update(GameManager* Scene)
{
	Scene;
	testObj_->Update();
	camera_.UpdateMatrix();
	postEffect_->Update();
}

void TestLevelDataScene::PostProcessDraw()
{
	postEffect_->PreDraw();
	testObj_->Draw(camera_);
	postEffect_->PostDraw();
}

void TestLevelDataScene::Back2dSpriteDraw()
{
}

void TestLevelDataScene::Object3dDraw()
{
	postEffect_->Draw(camera_);
}

void TestLevelDataScene::Flont2dSpriteDraw()
{
}
