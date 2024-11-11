#include "GameClearScene.h"
using namespace Engine::Manager;

void GameClearScene::Initialize()
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

	//gameOverText_ = make_unique<GameOverText>();
	//gameOverText_->Initialize();

	changeSceneAnimation_ = ChangeSceneAnimation::GetInstance();
	ui_ = make_unique<ClearSceneUI>();
	ui_->Initialize();
}

void GameClearScene::Update([[maybe_unused]]GameManager* Scene)
{

#ifdef _USE_IMGUI

	gameObjectManager_->ImGuiUpdate();
	ui_->ImGuiUpdate();

#endif // _USE_IMGUI

	changeSceneAnimation_->Update();


	//gameOverText_->Update();

	if (ChangeSceneAnimation::GetInstance()->GetIsComplite())
	{
		//gameOverUiManager_->Update();
	}

	ui_->Update();

	//if (gameOverUiManager_->GetIsSelect())
	{
		//changeSceneAnimation_->ChangeStart();
	}

	gameObjectManager_->Update();

	LightingManager::AddList(light_);
	PostEffect::GetInstance()->Update();

	//if (!gameOverUiManager_->GetIsSelect())

	if (!ChangeSceneAnimation::GetInstance()->GetIsChangeSceneFlag())
	{
		return;
	}
	////if (gameOverUiManager_->GetSelectIndex() == TITLE)
	//{
	//	Scene->ChangeScene(make_unique<TitleScene>());
	//	return;
	//}
	////if (gameOverUiManager_->GetSelectIndex() == GAME)
	//{
	//	Scene->ChangeScene(make_unique<GameScene>());
	//	return;
	//}	
	////if (gameOverUiManager_->GetSelectIndex() == SELECT)
	//{
	//	Scene->ChangeScene(make_unique<SelectScene>());
	//	return;
	//}
}

void GameClearScene::PostProcessDraw()
{
	gameObjectManager_->Draw();
}

void GameClearScene::Back2dSpriteDraw()
{
}

void GameClearScene::Object3dDraw()
{
	PostEffect::GetInstance()->Draw();
}

void GameClearScene::Flont2dSpriteDraw()
{
	ui_->Draw2d();
	changeSceneAnimation_->Draw();
}
