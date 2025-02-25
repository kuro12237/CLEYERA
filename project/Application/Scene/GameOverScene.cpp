#include "GameOverScene.h"

using namespace Engine::Manager;

void GameOverScene::Initialize([[maybe_unused]] GameManager *state)
{
   GlobalVariables::GetInstance()->SetDirectoryFilePath(
       "Resources/LevelData/ParamData/GameOverScene/");
   GlobalVariables::GetInstance()->LoadFiles("Resources/LevelData/ParamData/GameOverScene/");
   // levelDataの読み込み
   shared_ptr<LevelData> levelData =
       move(SceneFileLoader::GetInstance()->ReLoad(inputLevelDataFileName_));

   // objectManagerセット
   gameObjectManager_ = GameObjectManager::GetInstance();
   gameObjectManager_->ClearAllData();
   gameObjectManager_->MoveData(levelData.get());
   gameObjectManager_->SetAllParents();

   gameObjectManager_->CameraReset("Camera");
   gameObjectManager_->Update();

   gameOverText_ = make_unique<GameOverText>();
   gameOverText_->Initialize();

   gameOverUiManager_ = make_unique<GameOverUIManager>();
   gameOverUiManager_->Initialize();
   gameOverUiManager_->Update();

   changeSceneAnimation_ = ChangeSceneAnimation::GetInstance();

   ui_ = make_unique<GameOverSceneUI>();
   ui_->Initialize();

   this->jsonGropName_ = VAR_NAME(GameOverScene);
   this->CreateJsonData();

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

   Math::Vector::Vector4 fogParam = {};
   key = VAR_NAME(fogParam);
   AddJsonItem<decltype(fogParam)>(key, fogParam);
   fogParam = GetJsonItem<decltype(fogParam)>(key);

   postEffect_->GetAdjustedColorParam().fogScale_ = fogParam.x;
   postEffect_->GetAdjustedColorParam().fogAttenuationRate_ = fogParam.y;
   postEffect_->GetAdjustedColorParam().fogStart = fogParam.z;
   postEffect_->GetAdjustedColorParam().fogEnd = fogParam.w;
}

void GameOverScene::Update([[maybe_unused]] GameManager *Scene)
{

   changeSceneAnimation_->Update();

   ui_->Update();
   gameOverText_->Update();

   if (ChangeSceneAnimation::GetInstance()->GetIsComplite()) {
      gameOverUiManager_->Update();
   }

   if (gameOverUiManager_->GetIsSelect()) {
      changeSceneAnimation_->ChangeStart();
   }

   gameObjectManager_->Update();

   LightingManager::AddList(light_);

   if (!gameOverUiManager_->GetIsSelect()) {
      return;
   }

   if (!ChangeSceneAnimation::GetInstance()->GetIsChangeSceneFlag()) {
      return;
   }
   if (gameOverUiManager_->GetSelectIndex() == TITLE) {
      Scene->ChangeScene(make_unique<TitleScene>());
      return;
   }
   if (gameOverUiManager_->GetSelectIndex() == GAME) {
      Scene->ChangeScene(make_unique<GameScene>());
      return;
   }
   if (gameOverUiManager_->GetSelectIndex() == SELECT) {
      Scene->ChangeScene(make_unique<SelectScene>());
      return;
   }
}

void GameOverScene::ImGuiUpdate()
{

   gameObjectManager_->ImGuiUpdate();
   gameOverText_->ImGuiUpdate();
   ui_->ImGuiUpdate();
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
