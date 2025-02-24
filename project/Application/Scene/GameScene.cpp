#include "GameScene.h"

using namespace Engine;
using namespace Engine::Objects;
using namespace Engine::Manager;
using namespace Engine::Transform;

void GameScene::Initialize([[maybe_unused]] GameManager *state)
{
   // paramfilePath変更
   globalVariables_->SetDirectoryFilePath("Resources/LevelData/ParamData/GameScene/");
   globalVariables_->LoadFiles("Resources/LevelData/ParamData/GameScene/");

   this->jsonGropName_ = VAR_NAME(GameScene);
   this->CreateJsonData();

   // selectからのデータを移動
   selectSceneData_ = *state->GetMoveSceneContext()->GetData<SceneContextData>();

   // levelDataの読み込み
   inputLevelDataFileName_ = "LevelData_" + to_string(selectSceneData_.stageNumber + 1) + ".json";
   shared_ptr<LevelData> levelData =
       move(SceneFileLoader::GetInstance()->ReLoad(inputLevelDataFileName_));

   changeSceneAnmation_ = ChangeSceneAnimation::GetInstance();

   gameObjectManager_->ClearAllData();
   gameObjectManager_->MoveData(levelData.get());
   gameObjectManager_->SetAllParents();
   gameObjectManager_->CameraReset();
   gameObjectManager_->Update();

  
   // マネージャー初期化
   player_ = make_shared<PlayerManager>();
   managerList_.push_back(player_);

   enemyWalkManager_ = make_shared<EnemyWalkManager>();
   managerList_.push_back(enemyWalkManager_);

   bulletEnemyManager_ = make_shared<GunEnemyManager>();
   managerList_.push_back(bulletEnemyManager_);

   blockManager_ = make_shared<BlockManager>();
   managerList_.push_back(blockManager_);

   breakBlockManager_ = make_shared<BreakBlockManager>();
   managerList_.push_back(breakBlockManager_);

   warpManager_ = make_shared<WarpManager>();
   managerList_.push_back(warpManager_);

   stageCoinManager_ = make_shared<StageCoinManager>();
   managerList_.push_back(stageCoinManager_);

   gravityManager_ = make_shared<GravityManager>();
   managerList_.push_back(gravityManager_);

   lavaManager_ = make_shared<LavaManager>();
   managerList_.push_back(lavaManager_);

   for (weak_ptr<ManagerComponent> manager : managerList_) {
      manager.lock()->Initialize();
      manager.lock()->SetGameStartFlag(&isGameStartFlag_);
   }

   int32_t goalIndex = 0;
   string goalName = VAR_NAME(goalIndex);
   AddJsonItem<decltype(goalIndex)>(goalName, goalIndex);
   goalIndex = GetJsonItem<decltype(goalIndex)>(goalName);

   string lavaName = VAR_NAME(lavaIndex_);
   AddJsonItem<decltype(lavaIndex_)>(lavaName, lavaIndex_);
   lavaIndex_ = GetJsonItem<decltype(lavaIndex_)>(lavaName);



   // ライト
   light_ = make_shared<GameLight>();
   lightDataList_.push_back(light_);
   for (auto light : lightDataList_) {
      light.lock()->Initialize();
   }

   gameCollisionManager_ = make_unique<BoxCollisionManager>();

   // ゲーム終了のつなぐ
   isGameEnd_ = &player_->GetPlayerCore()->GetIsGameEnd();

   
   context_ = make_unique<ISceneContext>();

   // パーティクル
   wallHitParticle_ = make_unique<WallHitParticle>();
   particleList_.push_back(wallHitParticle_);

   playerDeadParticle_ = make_unique<PlayerDeadParticle>();
   particleList_.push_back(playerDeadParticle_);

   playerMoveParticle_ = make_unique<PlayerMoveParticle>();
   particleList_.push_back(playerMoveParticle_);

   deadParticle_ = make_unique<CharacterDeadParticle>();
   particleList_.push_back(deadParticle_);

   goalParticle_ = make_shared<GoalParticle>();
   goalParticle_->Initialize();

   for (auto obj : particleList_) {
      obj.lock()->Initialize();
   }

   particleList_.push_back(lavaManager_->GetLava(lavaIndex_).lock()->GetLavaParticle());

   // obj
   goal_ = make_unique<Goal>();
   goal_->SetGoalIndex(goalIndex);
   goal_->SetGoalObjectId(ObjectId::kGoalId);
   goal_->SetGoalParticle(goalParticle_);
   objctDataList_.push_back(goal_);

   for (weak_ptr<ObjectComponent> data : objctDataList_) {
      data.lock()->Initialize();
   }

   // 各クラスの設定
   enemyWalkManager_->SetDeadParticle(deadParticle_);

   player_->SetDeadParticle(playerDeadParticle_);
   player_->SetMoveParticle(playerMoveParticle_);
   player_->SetParticlePos();

#pragma region PostEffectSetting

   Math::Vector::Vector4 fogParam = {};
   string key = VAR_NAME(fogParam);
   AddJsonItem<decltype(fogParam)>(key, fogParam);
   fogParam = GetJsonItem<decltype(fogParam)>(key);

   postEffect_->GetAdjustedColorParam().fogScale_ = fogParam.x;
   postEffect_->GetAdjustedColorParam().fogAttenuationRate_ = fogParam.y;
   postEffect_->GetAdjustedColorParam().fogStart = fogParam.z;
   postEffect_->GetAdjustedColorParam().fogEnd = fogParam.w;

#pragma endregion

   this->ChangeGameSceneState(make_unique<GameSceneStartState>());
}

void GameScene::Update([[maybe_unused]] GameManager *Scene)
{
   changeSceneAnmation_->Update();

   if (state_) {
      state_->Update(this);
   }

   this->ListUpdate();

   ParticlesUpdate();

   Gravitys();
   Collision();

   /// シーン切り替え
   if (CheckChangeScene(Scene)) {
      return;
   }
}

bool GameScene::CheckChangeScene(GameManager *Scene)
{
   if (!changeSceneAnmation_->GetIsChangeSceneFlag()) {
      return false;
   }

   if (player_->GetHp()->GetHp() <= 0) {
      Scene->ChangeScene(make_unique<GameOverScene>());
      return true;
   }
   else {
      nextSceneData_.stageConinsCount = stageCoinManager_->GetCoinsCount();
      context_->SetData(nextSceneData_);

      Scene->SetMoveSceneContext(move(context_));
      Scene->ChangeScene(make_unique<GameClearScene>());
      return true;
   }
}

void GameScene::PostProcessDraw()
{
   gameObjectManager_->InstancingDraw();
   gameObjectManager_->NormalDraw();

   ParticlesDraw();
}

void GameScene::Flont2dSpriteDraw()
{

   if (state_) {
      state_->Draw2d();
   }

   changeSceneAnmation_->Draw();
}

void GameScene::ImGuiUpdate()
{
   gameObjectManager_->ImGuiUpdate();
   ImGui::Separator();
   ImGui::Text("SceneReload");
   static char buffer[256] = "";
   if (ImGui::InputText("SelectLevelDataFilePath", buffer, sizeof(buffer))) {
      inputLevelDataFileName_ = std::string(buffer);
   }
   ImGui::Separator();

   player_->ImGuiUpdate();

   if (ImGui::TreeNode("Particles")) {
      deadParticle_->ImGuiUpdate();
      ImGui::TreePop();
   }

   changeSceneAnmation_->ImGuiUpdate();

   if (state_) {
      state_->ImGuiUpdate();
   }
}

void GameScene::ChangeGameSceneState(unique_ptr<IGameSceneState> state)
{
   state_ = move(state);

   if (state_) {
      state_->Initialize(this);
      state_->Update(this);
   }
}

void GameScene::Collision()
{
   if (!player_->GetPlayerCore()->IsInState<PlayerStateGoalAnimation>()) {
      gameCollisionManager_->ListPushback(player_->GetPlayerCore());
   }
   for (size_t index = 0; index < player_->GetBullet().size(); index++) {
      if (player_->GetBullet()[index]) {
         gameCollisionManager_->ListPushback(player_->GetBullet()[index].get());
      }
   }

   for (shared_ptr<StageCoin> &coin : stageCoinManager_->GetCoins()) {
      if (coin) {
         gameCollisionManager_->ListPushback(coin.get());
      }
   }

   if (bulletEnemyManager_->GetIsStartFlag()) {
      for (auto &enemy : bulletEnemyManager_->GetGunEnemys()) {
         weak_ptr<GunEnemy> obj = enemy.core;
         auto it = obj.lock();
         if (it) {
            gameCollisionManager_->ListPushback(it.get());

            for (shared_ptr<GunEnemyBullet> &b : it->GetBullets()) {
               if (b) {
                  gameCollisionManager_->ListPushback(b.get());
               }
            }
         }

         for (auto &parts : enemy.parts) {
            if (!parts) {
               continue;
            }
            if (parts->GetIsEnd()) {
               gameCollisionManager_->ListPushback(parts.get());
            }
         }
      }
   }
   // 歩く敵
   for (shared_ptr<EnemyWalk> &e : enemyWalkManager_->GetData()) {
      weak_ptr<EnemyWalk> obj = e;
      auto it = obj.lock();
      if (it) {
         gameCollisionManager_->ListPushback(it.get());
      }
   }

   // ブロック
   for (shared_ptr<Block> b : blockManager_->GetBlocks()) {
      gameCollisionManager_->ListPushback(b.get());
   }
   // 壊れるブロック
   for (shared_ptr<BreakBlock> b : breakBlockManager_->GetBlocks()) {
      if (b) {
         weak_ptr<BreakBlock> it = b;
         auto obj = it.lock();
         gameCollisionManager_->ListPushback(obj.get());
      }
   }
   // ゴール
   gameCollisionManager_->ListPushback(goal_.get());

   // ワープ
   for (auto &warp : warpManager_->GetWarps()) {
      gameCollisionManager_->ListPushback(warp->GetWarpGate());
   }

   gameCollisionManager_->CheckAllCollisoin();

   gameCollisionManager_->End();
}

void GameScene::Gravitys()
{
   gravityManager_->ClearList();

   // managerの中のオブジェクトをリストに追加
   for (weak_ptr<ManagerComponent> obj : managerList_) {
      auto it = obj.lock();
      if (it) {
         it->GravityManagerObjListPush(gravityManager_);
      }
   }

   gravityManager_->PushParticleList(deadParticle_->GetParticle());
   gravityManager_->PushParticleList(
       lavaManager_->GetLava(lavaIndex_).lock()->GetLavaParticle().lock()->GetParticle());

   gravityManager_->CheckGravity();
}

void GameScene::ParticlesUpdate()
{
   deadParticle_->GetParticle()->CallBarrier();
   blockManager_->Dispach(deadParticle_->GetParticle());
   goalParticle_->Update();
}

void GameScene::ParticlesDraw()
{

   for (auto p : particleList_) {
      p.lock()->Draw();
   }
   goalParticle_->Draw();
}
