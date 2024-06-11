#include "TestLevelDataScene.h"

void TestLevelDataScene::Initialize()
{
	postEffect_ = make_unique<PostEffect>();
	postEffect_->Initialize("testScene");
	camera_.Initialize();
	camera_.translation_.z = -16.0f;
	CameraManager::GetInstance()->ResetCamera(camera_);

	levelData_ = SceneFileLoader::GetInstance()->ReLoad("TestSceneLoad_1.json");

	character_ = make_unique<TestCharacter>();

	character_->Initialize();

	for (const auto& [key, param] : levelData_->obj3dData)
	{
		if (key == character_->GetName())
		{
			character_->Create();
			character_->MoveData(param);
		}
	}
	levelData_->obj3dData.clear();

	debugCamera_ = make_unique<DebugCamera>();
	debugCamera_->Initialize();
	camera_.UpdateMatrix();

	light_.radious = 128.0f;
	light_.position.y = 64.0f;
	light_.decay = 0.25f;
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

	//object
	//instancing
	for (auto it = levelData_->objInstancing3dData.begin(); it != levelData_->objInstancing3dData.end(); ++it) {
		Game3dInstancingObjectData& data = it->second;
		uint32_t index = 0;
		for (shared_ptr<IGameInstancing3dObject>& transform : data.transform_)
		{
			transform->Update();
			data.GameInstancingObject->PushVector(transform, index);
			index++;
		}
		data.GameInstancingObject->Transfar();
	}

	debugCamera_->Update();
	camera_ = debugCamera_->GetData(camera_);

	//character_->Update();

	LightingManager::AddList(light_);
	postEffect_->Update();
}

void TestLevelDataScene::PostProcessDraw()
{
	postEffect_->PreDraw();

	character_->Draw();
	//gameObjectDraw

	//instancingDraw
	for (auto it = levelData_->objInstancing3dData.begin(); it != levelData_->objInstancing3dData.end(); ++it) {

		Game3dInstancingObjectData& data = it->second;
		data.GameInstancingObject->Draw();
	}

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
