#include "TestLevelDataScene.h"

void TestLevelDataScene::Initialize()
{
	postEffect_ = make_unique<PostEffect>();
	postEffect_->Initialize("testScene");
	camera_.Initialize();
	camera_.translation_.z = -16.0f;
	CameraManager::GetInstance()->ResetCamera(camera_);


	levelData_ = SceneFileLoader::GetInstance()->ReLoad("InstancingLoadTest.json");
	debugCamera_ = make_unique<DebugCamera>();
	debugCamera_->Initialize();
	camera_.UpdateMatrix();

	light_.radious = 128.0f;
	light_.position.y = 64.0f;
}

void TestLevelDataScene::Update(GameManager* Scene)
{
	Scene;
	debugCamera_->ImGuiUpdate();

	//object
	for (auto it = levelData_->obj3dData.begin(); it != levelData_->obj3dData.end(); ++it) {
		Game3dObjectData& data = it->second;
		data.worldTransform.UpdateMatrix();
    }

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

	LightingManager::AddList(light_);
	postEffect_->Update();
}

void TestLevelDataScene::PostProcessDraw()
{
	postEffect_->PreDraw();

	//gameObjectDraw
	for (auto it = levelData_->obj3dData.begin(); it != levelData_->obj3dData.end(); ++it) {
		Game3dObjectData& data = it->second;
		data.gameObject->Draw(data.worldTransform);
	}
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