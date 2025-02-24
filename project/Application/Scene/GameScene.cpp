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

   // Particle初期化
   ParticlesInitialize();

   GoalParticle::GetInstance()->Clear();
   CharacterDeadParticle::GetInstance()->GetEmitter()->AllClear();
   CharacterDeadParticle::GetInstance()->GetParticle()->Clear();

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

   // obj
   goal_ = make_unique<Goal>();
   goal_->SetGoalIndex(0);
   goal_->SetGoalObjectId(ObjectId::kGoalId);

   objctDataList_.push_back(goal_);

   for (weak_ptr<ObjectComponent> data : objctDataList_) {
      data.lock()->Initialize();
   }

   // ライト
   light_ = make_shared<GameLight>();
   lightDataList_.push_back(light_);
   for (auto light : lightDataList_) {
      light.lock()->Initialize();
   }

   gameCollisionManager_ = make_unique<BoxCollisionManager>();

  
   // ゲーム終了のつなぐ
   isGameEnd_ = &player_->GetPlayerCore()->GetIsGameEnd();

   // シーンコンテキスト
   context_ = make_unique<ISceneContext>();

   // パーティクル
   wallHitParticle_ = make_unique<WallHitParticle>();
   wallHitParticle_->Initialize();
   particleList_.push_back(wallHitParticle_);
   particleList_.push_back(lavaManager_->GetLava(0).lock()->GetLavaParticle());

   PostEffect::GetInstance()->GetAdjustedColorParam().fogScale_ = 1.0f;
   PostEffect::GetInstance()->GetAdjustedColorParam().fogAttenuationRate_ = 1.0f;
   PostEffect::GetInstance()->GetAdjustedColorParam().fogStart = 200.0f;
   PostEffect::GetInstance()->GetAdjustedColorParam().fogEnd = 900.0f;

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
      contextData_.stageConinsCount = stageCoinManager_->GetCoinsCount();
      context_->SetData(contextData_);

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
      GoalParticle::GetInstance()->ImGuiUpdate();
      characterDeadParticle_->ImGuiUpdate();
      characterMoveParticle_->ImGuiUpdate();
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
   for (weak_ptr<ManagerComponent> m : managerList_) {
      auto mObj = m.lock();
      if (mObj) {

         mObj->GravityManagerObjListPush(gravityManager_.get());
      }
   }

   gravityManager_->PushParticleList(CharacterDeadParticle::GetInstance()->GetParticle());
   gravityManager_->PushParticleList(
       lavaManager_->GetLava(0).lock()->GetLavaParticle().lock()->GetParticle());

   gravityManager_->CheckGravity();
}

void GameScene::ParticlesInitialize()
{
   characterDeadParticle_ = CharacterDeadParticle::GetInstance();
   characterDeadParticle_->Initialize();

   characterMoveParticle_ = CharacterMoveParticle::GetInstance();
   characterMoveParticle_->Initialize();
}

void GameScene::ParticlesUpdate()
{
   characterDeadParticle_->GetParticle()->CallBarrier();
   blockManager_->Dispach(characterDeadParticle_->GetParticle());

   characterDeadParticle_->Update();

   characterMoveParticle_->Update();
   wallHitParticle_->Update();

   GoalParticle::GetInstance()->Update();
}

void GameScene::ParticlesDraw()
{
   GoalParticle::GetInstance()->Draw();
   characterDeadParticle_->Draw();

   for (auto p : particleList_) {
      p.lock()->Draw();
   }

   wallHitParticle_->Draw();

   player_->DrawParticle();
}
