#include "TestScene.h"

void TestScene::Initialize()
{
	PostEffect::GetInstance()->Initialize("testScene2");


	camera_.Initialize();
	camera_.translation_.z = -16.0f;
	camera_.translation_.y = 2.0f;
	CameraManager::GetInstance()->ResetCamera(camera_);
	desc_;

	gameObject_ = make_unique<Game3dObject>();
	gameObject_->SetDesc(desc_);
	gameObject_->Create(make_unique<Phong3dPipline>());

	ModelManager::GetInstance()->LoadObjectFile("TestGround");
	//gameObject_->SetModel(ModelManager::GetInstance()->LoadObjectFile("TestGround"));


	wT_.Initialize();
	light_.radious = 128.0f;
	light_.position.y = 64.0f;
	light_.decay = 0.1f;

}

void TestScene::Update(GameManager* Scene)
{

	Scene;

	if (ImGui::Button("sceneChange"))
	{
		Scene->ChangeState(new TestLevelDataScene);
		return;
	}

	wT_.UpdateMatrix();
	camera_.UpdateMatrix();

	PostEffect::GetInstance()->Update();
	LightingManager::AddList(light_);
}

void TestScene::PostProcessDraw()
{
	//PostEffect::GetInstance()->PreDraw();

	//gameObject_->Draw(wT_);

	//PostEffect::GetInstance()->PostDraw();
}

void TestScene::Back2dSpriteDraw()
{
}

void TestScene::Object3dDraw()
{
	//PostEffect::GetInstance()->Draw(camera_);
}

void TestScene::Flont2dSpriteDraw()
{
}
