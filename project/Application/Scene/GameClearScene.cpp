#include "GameClearScene.h"
using namespace Engine::Manager;

void GameClearScene::Initialize([[maybe_unused]]GameManager* state)
{
	GlobalVariables::GetInstance()->SetDirectoryFilePath("Resources/LevelData/ParamData/GameClearScene/");
	GlobalVariables::GetInstance()->LoadFiles("Resources/LevelData/ParamData/GameClearScene/");
	//levelDataÇÃì«Ç›çûÇ›
	shared_ptr<LevelData> levelData = move(SceneFileLoader::GetInstance()->ReLoad(inputLevelDataFileName_));

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

	changeSceneAnimation_ = ChangeSceneAnimation::GetInstance();

	this->SetFlont2dSpriteDrawFunc(std::bind(&GameClearScene::Flont2dSpriteDraw, this));
	this->SetPostEffectDrawFunc(std::bind(&GameClearScene::PostProcessDraw, this));

	gaameClearText_ = make_unique<GameClearText>();
	gaameClearText_->Initialize();

	contextData_ = *state->GetMoveSceneContext()->GetData<SceneContextData>();

	ui_ = make_unique<ClearSceneUI>();

	ui_->SetStageCoin(contextData_.stageConinsCount);
	ui_->Initialize();

	character_ = make_unique<ClearCharacter>();
	character_->Initialize();

	camera_ = make_unique<ClearCamera>();
	camera_->Initilaize();
	

	fireParticle_ = make_unique<FireParticle>();
	fireParticle_->Initialize();

}

void GameClearScene::Update([[maybe_unused]] GameManager* Scene)
{

#ifdef _USE_IMGUI

	gameObjectManager_->ImGuiUpdate();
	ui_->ImGuiUpdate();

	fireParticle_->ImGuiUpdate();
#endif // _USE_IMGUI

	changeSceneAnimation_->Update();


	if (ChangeSceneAnimation::GetInstance()->GetIsComplite())
	{
	}

	fireParticle_->Emit();
	fireParticle_->Update();

	ui_->Update();
	gaameClearText_->Update();

	character_->Update();

	camera_->Update();


	gameObjectManager_->Update();

	LightingManager::AddList(light_);

	if (ui_->GetIsSelect())
	{
		changeSceneAnimation_->ChangeStart();
	}

	if (!ChangeSceneAnimation::GetInstance()->GetIsChangeSceneFlag())
	{
		return;
	}

	if (ui_->GetNextStage() == ClearSceneChangeScene::Title)
	{
		Scene->ChangeScene(make_unique<TitleScene>());
		return;
	}
	if (ui_->GetNextStage() == ClearSceneChangeScene::Select)
	{
		Scene->ChangeScene(make_unique<SelectScene>());
		return;
	}

}

void GameClearScene::PostProcessDraw()
{
	gameObjectManager_->Draw();
	fireParticle_->Draw();

}

void GameClearScene::Flont2dSpriteDraw()
{

	ui_->Draw2d();
	changeSceneAnimation_->Draw();
}
