#include "GameOverScene.h"

using namespace Engine::Manager;

void GameOverScene::Initialize([[maybe_unused]] GameManager* state)
{
	GlobalVariables::GetInstance()->SetDirectoryFilePath("Resources/LevelData/ParamData/GameOverScene/");
	GlobalVariables::GetInstance()->LoadFiles("Resources/LevelData/ParamData/GameOverScene/");
	//levelDataの読み込み
	shared_ptr<LevelData> levelData = move(SceneFileLoader::GetInstance()->ReLoad(inputLevelDataFileName_));

	//objectManagerセット
	gameObjectManager_ = GameObjectManager::GetInstance();
	gameObjectManager_->ClearAllData();
	gameObjectManager_->MoveData(levelData.get());
	gameObjectManager_->SetAllParents();

	gameObjectManager_->CameraReset("Camera");
	gameObjectManager_->Update();

	light_.radious = 512.0f;
	light_.position.y = 64.0f;
	light_.position.z = -16.0f;
	light_.decay = 0.1f;

	gameOverText_ = make_unique<GameOverText>();
	gameOverText_->Initialize();

	gameOverUiManager_ = make_unique<GameOverUIManager>();
	gameOverUiManager_->Initialize();
	gameOverUiManager_->Update();

	changeSceneAnimation_ = ChangeSceneAnimation::GetInstance();

	ui_ = make_unique<GameOverSceneUI>();
	ui_->Initialize();

	this->SetFlont2dSpriteDrawFunc(std::bind(&GameOverScene::Flont2dSpriteDraw, this));
	this->SetPostEffectDrawFunc(std::bind(&GameOverScene::PostProcessDraw, this));

	//fog設定
	Engine::PostEffect::GetInstance()->GetAdjustedColorParam().fogScale_ = 0.5f;
	Engine::PostEffect::GetInstance()->GetAdjustedColorParam().fogAttenuationRate_ = 0.5f;
	Engine::PostEffect::GetInstance()->GetAdjustedColorParam().fogStart = 70.0f;
	Engine::PostEffect::GetInstance()->GetAdjustedColorParam().fogEnd = 280.0f;
}

void GameOverScene::Update([[maybe_unused]] GameManager* Scene)
{
#ifdef _USE_IMGUI

	gameObjectManager_->ImGuiUpdate();
	gameOverText_->ImGuiUpdate();
	ui_->ImGuiUpdate();
#endif // _USE_IMGUI

	changeSceneAnimation_->Update();

	ui_->Update();
	gameOverText_->Update();

	if (ChangeSceneAnimation::GetInstance()->GetIsComplite())
	{
		gameOverUiManager_->Update();
	}

	if (gameOverUiManager_->GetIsSelect())
	{
		changeSceneAnimation_->ChangeStart();
	}

	gameObjectManager_->Update();

	LightingManager::AddList(light_);
	
	if (!gameOverUiManager_->GetIsSelect())
	{
		return;
	}

	if (!ChangeSceneAnimation::GetInstance()->GetIsChangeSceneFlag())
	{
		return;
	}
	if (gameOverUiManager_->GetSelectIndex() == TITLE)
	{
		Scene->ChangeScene(make_unique<TitleScene>());
		return;
	}
	if (gameOverUiManager_->GetSelectIndex() == GAME)
	{
		Scene->ChangeScene(make_unique<GameScene>());
		return;

	}	if (gameOverUiManager_->GetSelectIndex() == SELECT)
	{
		Scene->ChangeScene(make_unique<SelectScene>());
		return;
	}

}

void GameOverScene::PostProcessDraw()
{

	gameObjectManager_->InstancingDraw();
	gameObjectManager_->NormalDraw();
}


void GameOverScene::Flont2dSpriteDraw()
{
	gameOverUiManager_->Draw2d();
	gameOverText_->Draw2d();
	ui_->Draw2d();

	changeSceneAnimation_->Draw();
}
