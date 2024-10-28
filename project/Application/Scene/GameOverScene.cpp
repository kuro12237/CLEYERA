#include "GameOverScene.h"

using namespace Engine::Manager;

void GameOverScene::Initialize()
{
	//levelData‚Ì“Ç‚Ýž‚Ý
	levelData_ = SceneFileLoader::GetInstance()->ReLoad(inputLevelDataFileName_);

	gameObjectManager_ = GameObjectManager::GetInstance();
	gameObjectManager_->ClearAllData();
	gameObjectManager_->CopyData(levelData_.get());
	gameObjectManager_->SetAllParents();
	gameObjectManager_->CameraReset("Camera");
	gameObjectManager_->Update();


	light_.radious = 512.0f;
	light_.position.y = 64.0f;
	light_.position.z = -16.0f;
	light_.decay = 0.1f;
}

void GameOverScene::Update([[maybe_unused]] GameManager* Scene)
{
	gameObjectManager_->ImGuiUpdate();

	gameObjectManager_->Update();

	LightingManager::AddList(light_);
	PostEffect::GetInstance()->Update();
}

void GameOverScene::PostProcessDraw()
{
	gameObjectManager_->Draw();
}

void GameOverScene::Back2dSpriteDraw()
{
}

void GameOverScene::Object3dDraw()
{
	PostEffect::GetInstance()->Draw();
}

void GameOverScene::Flont2dSpriteDraw()
{
}
