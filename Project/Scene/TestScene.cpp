#include "TestScene.h"

void TestScene::Initialize()
{
	postEffect_ = make_unique<PostEffect>();
	postEffect_->Initialize("testScene2");


	camera_.Initialize();
	camera_.translation_.z = -16.0f;
	camera_.translation_.y = 2.0f;
	CameraManager::GetInstance()->ResetCamera(camera_);
	desc_;

	gameObject_ = make_unique<Game3dObject>();
	gameObject_->SetDesc(desc_);
	gameObject_->Create(make_unique<Phong3dPipline>());
	
	
	gameObject_->SetModel(ModelManager::LoadObjectFile("TestGround"));


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

	postEffect_->Update();
	LightingManager::AddList(light_);
}

void TestScene::PostProcessDraw()
{
	postEffect_->PreDraw();

	gameObject_->Draw(wT_);

	postEffect_->PostDraw();
}

void TestScene::Back2dSpriteDraw()
{
}

void TestScene::Object3dDraw()
{

	postEffect_->Draw(camera_);
}

void TestScene::Flont2dSpriteDraw()
{
}
