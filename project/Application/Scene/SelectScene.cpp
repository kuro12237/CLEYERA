#include "SelectScene.h"

using namespace Engine::Manager;

void SelectScene::Initialize([[maybe_unused]] GameManager *state)
{
   GlobalVariables::GetInstance()->SetDirectoryFilePath(
       "Resources/LevelData/ParamData/SelectScene/");
   GlobalVariables::GetInstance()->LoadFiles("Resources/LevelData/ParamData/SelectScene/");

   // levelDataの読み込み
   shared_ptr<LevelData> levelData =
       move(SceneFileLoader::GetInstance()->ReLoad(inputLevelDataFileName_));

   gameObjectManager_ = GameObjectManager::GetInstance();
   gameObjectManager_->ClearAllData();
   gameObjectManager_->MoveData(levelData.get());
   gameObjectManager_->SetAllParents();
   gameObjectManager_->CameraReset();
   gameObjectManager_->Update();

   goalParticle_ = make_unique<GoalParticle>();
   goalParticle_->Initialize();

   player_ = make_unique<PlayerManager>();
   player_->Initialize();

   goals_.resize(portalMax_);

   for (size_t portalIndex = 0; portalIndex < portalMax_; portalIndex++) {
      shared_ptr<Goal> goal = make_shared<Goal>();
      goals_[portalIndex] = make_shared<Goal>();
      goals_[portalIndex]->SetGoalObjectId(ObjectId::kGoalId);
      goals_[portalIndex]->SetGoalIndex(uint32_t(portalIndex));
      goals_[portalIndex]->SetGoalParticle(goalParticle_);
      goals_[portalIndex]->Initialize();
   }

   blockManager_ = make_shared<BlockManager>();
   blockManager_->Initialize();
   gameCollisionManager_ = make_unique<BoxCollisionManager>();
   gravityManager_ = make_unique<GravityManager>();
   gravityManager_->Initialize();

   lava_ = make_unique<Lava>();
   lava_->Initialize();

   this->jsonGropName_ = VAR_NAME(SelectScene);
   this->CreateJsonData();

   float lightRadious = 512.0f;
   Math::Vector::Vector3 lightPos = {0.0f, 64.0f, -16.0f};
   float lightDecay = 0.1f;

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

   isGameEnd_ = &player_->GetPlayerCore()->GetIsGameEnd();
   player_->SetGameStartFlag(&isGameStart_);

   context_ = make_unique<ISceneContext>();

   SkyBox::GetInstance()->Reset();
   const float kSkyBoxScale_ = 256.0f;
   SkyBox::GetInstance()->SetTransform({{kSkyBoxScale_, kSkyBoxScale_, kSkyBoxScale_}});
   uint32_t skyBoxTexHandle = TextureManager::LoadDDSTexture("SkyBox/CubeMap.dds");
   SkyBox::GetInstance()->SetTexHandle(skyBoxTexHandle);

   Math::Vector::Vector4 fogParam = {};
   key = VAR_NAME(fogParam);
   AddJsonItem<decltype(fogParam)>(key, fogParam);
   fogParam = GetJsonItem<decltype(fogParam)>(key);

   postEffect_->GetAdjustedColorParam().fogScale_ = fogParam.x;
   postEffect_->GetAdjustedColorParam().fogAttenuationRate_ = fogParam.y;
   postEffect_->GetAdjustedColorParam().fogStart = fogParam.z;
   postEffect_->GetAdjustedColorParam().fogEnd = fogParam.w;

   ui_ = make_unique<SelectSceneUI>();
   ui_->Initialize();

   stageNumbers_.resize(portalMax_);

   for (size_t i = 0; i < portalMax_; i++) {
      stageNumbers_[i] = make_unique<StageNumber>();
      stageNumbers_[i]->SetNum(uint32_t(i) + 1);
      stageNumbers_[i]->Initialize();
   }
}

void SelectScene::Update(GameManager *Scene)
{

   ChangeSceneAnimation::GetInstance()->Update();

   // シーン切替が終わったら
   if (ChangeSceneAnimation::GetInstance()->GetIsComplite()) {
      isGameStart_ = true;
   }

   player_->Update();

   for (size_t i = 0; i < portalMax_; i++) {
      goals_[i]->Update();
   }

   for (size_t i = 0; i < portalMax_; i++) {
      stageNumbers_[i]->Update();
   }

   SkyBox::GetInstance()->Update();
   goalParticle_->Update();
   lava_->Update();

   blockManager_->Update();

   LightingManager::AddList(light_);

   Gravitys();

   Collision();

   gameObjectManager_->Update();

   ui_->Update();

   for (size_t i = 0; i < goals_.size(); i++) {
      if (goals_[i]->GetIsGoalFlag()) {

         ChangeSceneAnimation::GetInstance()->ChangeStart();
      }
   }

   if (ChangeSceneAnimation::GetInstance()->GetIsChangeSceneFlag()) {
      int32_t stageNumber = 0;
      for (size_t i = 0; i < goals_.size(); i++) {
         if (goals_[i]->GetIsGoalFlag()) {
            stageNumber = int32_t(i);
         }
      }

      contextData_.stageNumber = stageNumber;
      context_->SetData(contextData_);
      Scene->SetMoveSceneContext(move(context_));
      Scene->ChangeScene(make_unique<GameScene>());
      return;
   }

   gameCollisionManager_->End();
}

void SelectScene::ImGuiUpdate()
{

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
   gameObjectManager_->ImGuiUpdate();
   if (ImGui::TreeNode("light")) {
      ImGui::DragFloat3("t", &light_.position.x);
      ImGui::DragFloat("radious", &light_.radious);
      ImGui::DragFloat("decay", &light_.decay);
      ImGui::DragFloat("intencity", &light_.intencity);

      ImGui::TreePop();
   }

   ui_->ImGuiUpdate();
   ChangeSceneAnimation::GetInstance()->ImGuiUpdate();
}

void SelectScene::PostProcessDraw()
{

   gameObjectManager_->InstancingDraw();
   gameObjectManager_->NormalDraw();

   lava_->GetLavaParticle().lock()->Draw();

   goalParticle_->Draw();
}

void SelectScene::Flont2dSpriteDraw()
{
   player_->Draw2d();
   player_->Draw2dBullet();
   ui_->Draw2d();
   ChangeSceneAnimation::GetInstance()->Draw();
}

void SelectScene::Collision()
{
   // プレイヤー本体
   if (!player_->GetPlayerCore()->IsInState<PlayerStateGoalAnimation>()) {
      gameCollisionManager_->ListPushback(player_->GetPlayerCore());
   }
   // playerの弾
   for (size_t index = 0; index < player_->GetBullet().size(); index++) {
      if (player_->GetBullet()[index]) {
         gameCollisionManager_->ListPushback(player_->GetBullet()[index].get());
      }
   }
   // ブロック
   for (shared_ptr<Block> b : blockManager_->GetBlocks()) {
      gameCollisionManager_->ListPushback(b.get());
   }
   // portal
   for (shared_ptr<Goal> g : goals_) {
      gameCollisionManager_->ListPushback(g.get());
   }

   gameCollisionManager_->CheckAllCollisoin();
}

void SelectScene::Gravitys()
{
   gravityManager_->Update();
   gravityManager_->ClearList();

   if (!player_->GetPlayerCore()->IsInState<PlayerStateGoalAnimation>()) {
      gravityManager_->PushList(player_->GetPlayerCore());
   }
   gravityManager_->PushParticleList(lava_->GetLavaParticle().lock()->GetParticle());

   gravityManager_->CheckGravity();
}

bool SelectScene::CheckLoadScene()
{
   bool changeFlag = false;

   // プレイヤーと当たったidがportalIdが一致していた場合
   queue<uint32_t> allHitIds = player_->GetPlayerCore()->GetCollider()->GetAllHitIds();
   size_t size = allHitIds.size();

   for (size_t id = 0; id < size; id++) {
      uint32_t hitId = allHitIds.front();
      allHitIds.pop();
      for (size_t portalCount = 0; portalCount < portalMax_; portalCount++) {
         if (hitId == ObjectId::kPortalIds[portalCount]) {
            changeFlag = true;
         }
      }
   }
   return changeFlag;
}
