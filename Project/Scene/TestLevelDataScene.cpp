#include "TestLevelDataScene.h"

void TestLevelDataScene::Initialize()
{
	postEffect_ = make_unique<PostEffect>();
	postEffect_->Initialize("testScene");
	camera_.Initialize();
	camera_.translation_.z = -16.0f;
	CameraManager::GetInstance()->ResetCamera(camera_);

	levelData_= SceneFileLoader::GetInstance()->ReLoad("TestSceneLoad_1.json");

	objectManager_ = make_unique<GameObjectManager>();
	objectManager_->CopyData(levelData_.get());

	debugCamera_ = make_unique<DebugCamera>();
	debugCamera_->Initialize();
	camera_.UpdateMatrix();

	light_.radious = 128.0f;
	light_.position.y = 64.0f;
	light_.decay = 0.25f;

	player_ = make_unique<Player>();
	player_->Initialize();
	player_->GetData(objectManager_.get());
	
}

void TestLevelDataScene::Update(GameManager* Scene)
{
	Scene;
#ifdef _USE_IMGUI

	debugCamera_->ImGuiUpdate();

	if (ImGui::TreeNode("light"))
	{
		ImGui::DragFloat3("t", &light_.position.x);
		ImGui::TreePop();
	}

	if (ImGui::Button("sceneReload_1"))
	{
		levelData_ = SceneFileLoader::GetInstance()->ReLoad("TestSceneLoad_1.json");
		return;
	}
	if (ImGui::Button("sceneReload_2"))
	{
		levelData_ = SceneFileLoader::GetInstance()->ReLoad("TestSceneLoad_2.json");
		return;
	}
#endif // _USE_IMGUI

	player_->Update();

	objectManager_->ObjDataUpdate(player_.get());

	objectManager_->Update();

	debugCamera_->Update();
	camera_ = debugCamera_->GetData(camera_);

	LightingManager::AddList(light_);
	postEffect_->Update();
}

void TestLevelDataScene::PostProcessDraw()
{
	postEffect_->PreDraw();

	objectManager_->Draw();

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
