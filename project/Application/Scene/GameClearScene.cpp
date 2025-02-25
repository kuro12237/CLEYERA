#include "GameClearScene.h"
using namespace Engine::Manager;

void GameClearScene::Initialize([[maybe_unused]] GameManager *state)
{
   globalVariables_->SetDirectoryFilePath("Resources/LevelData/ParamData/GameClearScene/");
   globalVariables_->LoadFiles("Resources/LevelData/ParamData/GameClearScene/");

   changeSceneAnimation_ = ChangeSceneAnimation::GetInstance();

   // levelDataの読み込み
   shared_ptr<LevelData> levelData =
       move(SceneFileLoader::GetInstance()->ReLoad(inputLevelDataFileName_));

   this->jsonGropName_ = VAR_NAME(GameClearScene);
   this->CreateJsonData();

   gameObjectManager_->ClearAllData();
   gameObjectManager_->MoveData(levelData.get());
   gameObjectManager_->SetAllParents();
   gameObjectManager_->CameraReset("Camera");
   gameObjectManager_->Update();

   // データ引継ぎ
   contextData_ = *state->GetMoveSceneContext()->GetData<SceneContextData>();

   ui_ = make_unique<ClearSceneUI>();
   ui_->SetStageCoin(contextData_.stageConinsCount);
   ui_->Initialize();

   character_ = make_unique<ClearCharacter>();
   character_->Initialize();

   camera_ = make_unique<ClearCamera>();
   camera_->Initialize();

   explosionParticle_ = make_unique<ExplosionParticle>();
   explosionParticle_->Initialize();

   coinManager_ = make_unique<ClearCoinManager>();
   coinManager_->CoinsCount(contextData_.stageConinsCount);
   coinManager_->Initialize();

   lava_ = make_unique<Lava>();
   lava_->Initialize();

   gravityManager_ = make_unique<GravityManager>();
   gravityManager_->Initialize();

   float lightRadious = 0.0f;
   Math::Vector::Vector3 lightPos = {};
   float lightDecay = 0.0f;

   string key = VAR_NAME(lightRadious);
   AddJsonItem<decltype(lightRadious)>(key, lightRadious);
   lightRadious = GetJsonItem<decltype(lightRadious)>(key);

   key = VAR_NAME(lightPos);
   AddJsonItem<decltype(lightPos)>(key, lightPos);
   lightPos = GetJsonItem<decltype(lightPos)>(key);

   key = VAR_NAME(lightDecay);
   AddJsonItem<decltype(lightDecay)>(key, lightDecay);
   lightDecay = GetJsonItem<decltype(lightDecay)>(key);

   light_.radious = lightRadious;
   light_.position = lightPos;
   light_.decay = lightDecay;

#pragma region PostEffectSetting

   Math::Vector::Vector4 fogParam = {};
   key = VAR_NAME(fogParam);
   AddJsonItem<decltype(fogParam)>(key, fogParam);
   fogParam = GetJsonItem<decltype(fogParam)>(key);

   postEffect_->GetAdjustedColorParam().fogScale_ = fogParam.x;
   postEffect_->GetAdjustedColorParam().fogAttenuationRate_ = fogParam.y;
   postEffect_->GetAdjustedColorParam().fogStart = fogParam.z;
   postEffect_->GetAdjustedColorParam().fogEnd = fogParam.w;

#pragma endregion
}

void GameClearScene::Update([[maybe_unused]] GameManager *Scene)
{

   changeSceneAnimation_->Update();

   explosionParticle_->Update();

   ui_->Update();

   character_->Update();

   camera_->Update();

   if (camera_->GetIsComplite() && !coinManager_->GetIsAnimStart()) {
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

   if (ui_->GetIsSelect()) {
      changeSceneAnimation_->ChangeStart();
   }

   if (!ChangeSceneAnimation::GetInstance()->GetIsChangeSceneFlag()) {
      return;
   }

   if (ui_->GetNextStage() == ClearSceneChangeScene::Title) {
      Scene->ChangeScene(make_unique<TitleScene>());
      return;
   }
   if (ui_->GetNextStage() == ClearSceneChangeScene::Select) {
      Scene->ChangeScene(make_unique<SelectScene>());
      return;
   }
}

void GameClearScene::ImGuiUpdate() {

   gameObjectManager_->ImGuiUpdate();
   ui_->ImGuiUpdate();

   lava_->Update();
   coinManager_->ImGuiUpdate();
   ImGui::Begin("PostEffect");
   ImGui::DragFloat("scale::%f",
                    &Engine::PostEffect::GetInstance()->GetAdjustedColorParam().fogScale_, 0.01f);
   ImGui::DragFloat("att::%f",
                    &Engine::PostEffect::GetInstance()->GetAdjustedColorParam().fogAttenuationRate_,
                    0.01f);
   ImGui::DragFloat("start::%f",
                    &Engine::PostEffect::GetInstance()->GetAdjustedColorParam().fogStart, 1.0f);
   ImGui::DragFloat("end::%f", &Engine::PostEffect::GetInstance()->GetAdjustedColorParam().fogEnd,
                    1.0f);
   ImGui::End();

   explosionParticle_->ImGuiUpdate();
}

void GameClearScene::PostProcessDraw()
{
   gameObjectManager_->InstancingDraw();
   coinManager_->ParticleDraw();
   gameObjectManager_->NormalDraw();

   explosionParticle_->Draw();
   lava_->GetLavaParticle().lock()->Draw();
}

void GameClearScene::Flont2dSpriteDraw()
{
   ui_->Draw2d();

   changeSceneAnimation_->Draw();
}
