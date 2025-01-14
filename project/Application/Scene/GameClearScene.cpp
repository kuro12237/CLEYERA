#include "GameClearScene.h"
using namespace Engine::Manager;

void GameClearScene::Initialize([[maybe_unused]] GameManager* state)
{
	GlobalVariables::GetInstance()->SetDirectoryFilePath("Resources/LevelData/ParamData/GameClearScene/");
	GlobalVariables::GetInstance()->LoadFiles("Resources/LevelData/ParamData/GameClearScene/");

	gameObjectManager_ = GameObjectManager::GetInstance();
	changeSceneAnimation_ = ChangeSceneAnimation::GetInstance();

	this->SetFlont2dSpriteDrawFunc(std::bind(&GameClearScene::Flont2dSpriteDraw, this));
	this->SetPostEffectDrawFunc(std::bind(&GameClearScene::PostProcessDraw, this));


	//levelDataの読み込み
	shared_ptr<LevelData> levelData = move(SceneFileLoader::GetInstance()->ReLoad(inputLevelDataFileName_));

	gameObjectManager_->ClearAllData();
	gameObjectManager_->MoveData(levelData.get());
	gameObjectManager_->SetAllParents();

	gameObjectManager_->CameraReset("Camera");
	gameObjectManager_->Update();

	//データ引継ぎ
	contextData_ = *state->GetMoveSceneContext()->GetData<SceneContextData>();


	ui_ = make_unique<ClearSceneUI>();
	ui_->SetStageCoin(contextData_.stageConinsCount);
	ui_->Initialize();

	character_ = make_unique<ClearCharacter>();
	character_->Initialize();

	camera_ = make_unique<ClearCamera>();
	camera_->Initilaize();


	explosionParticle_ = make_unique<ExplosionParticle>();
	explosionParticle_->Initialize();

	coinManager_ = make_unique<ClearCoinManager>();

	coinManager_->CoinsCount(contextData_.stageConinsCount);
	coinManager_->Initilaize();

	lava_ = make_unique<Lava>();
	lava_->Initialize();

	gravityManager_ = make_unique<GravityManager>();
	gravityManager_->Initialize();

	light_.radious = 512.0f;
	light_.position.y = 16.0f;
	light_.position.z = -16.0f;
	light_.decay = 0.1f;

	//fog設定
	Engine::PostEffect::GetInstance()->GetAdjustedColorParam().fogScale_ = 0.5f;
	Engine::PostEffect::GetInstance()->GetAdjustedColorParam().fogAttenuationRate_ = 0.5f;
	Engine::PostEffect::GetInstance()->GetAdjustedColorParam().fogStart = 70.0f;
	Engine::PostEffect::GetInstance()->GetAdjustedColorParam().fogEnd = 280.0f;
}

void GameClearScene::Update([[maybe_unused]] GameManager* Scene)
{
#ifdef _USE_IMGUI

	gameObjectManager_->ImGuiUpdate();
	ui_->ImGuiUpdate();

	lava_->Update();
	coinManager_->ImGuiUpdate();

	if (ImGui::Button("ResetScene"))
	{

		Scene->ChangeScene(make_unique<GameClearScene>());
		return;
	}
	ImGui::Begin("PostEffect");
	ImGui::DragFloat("scale::%f", &Engine::PostEffect::GetInstance()->GetAdjustedColorParam().fogScale_, 0.01f);
	ImGui::DragFloat("att::%f", &Engine::PostEffect::GetInstance()->GetAdjustedColorParam().fogAttenuationRate_, 0.01f);
	ImGui::DragFloat("start::%f", &Engine::PostEffect::GetInstance()->GetAdjustedColorParam().fogStart, 1.0f);
	ImGui::DragFloat("end::%f", &Engine::PostEffect::GetInstance()->GetAdjustedColorParam().fogEnd, 1.0f);
	ImGui::End();

	explosionParticle_->ImGuiUpdate();

#endif // _USE_IMGUI

	changeSceneAnimation_->Update();


	explosionParticle_->Update();

	ui_->Update();

	character_->Update();

	camera_->Update();

	if (camera_->GetIsComplite() && !coinManager_->GetIsAnimStart())
	{
		coinManager_->SetIsAnimStart(true);
	}


	ui_->SetIsCearTextUIAnimStart(true);


	coinManager_->Update();

	gravityManager_->Update();
	gravityManager_->ClearList();

	gravityManager_->PushParticleList(explosionParticle_->GetParticle());
	gravityManager_->CheckGravity();

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
	gameObjectManager_->InstancingDraw();
	coinManager_->ParticleDraw();
	gameObjectManager_->NormalDraw();


	explosionParticle_->Draw();
	lava_->GetLavaParticle()->Draw();
}

void GameClearScene::Flont2dSpriteDraw()
{
	ui_->Draw2d();

	changeSceneAnimation_->Draw();
}
