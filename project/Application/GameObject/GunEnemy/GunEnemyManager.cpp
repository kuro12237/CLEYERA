#include "GunEnemyManager.h"

void GunEnemyManager::Initialize()
{
   gameObjectManager_ = GameObjectManager::GetInstance();

   const string name = "GunEnemyCore";
   const string leftName = "GunEnemyLeft";
   const string rightName = "GunEnemyRight";
   const string barrelName = "GunEnemyBarrel";

   for (uint32_t index = 0; index < uint32_t(gameObjectManager_->GetObj3dDatas().size()); index++) {
      vector<string> names{name + FormatNumberWithDots(enemyCount_),
                           leftName + FormatNumberWithDots(enemyCount_),
                           rightName + FormatNumberWithDots(enemyCount_),
                           barrelName + FormatNumberWithDots(enemyCount_)};

      if (gameObjectManager_->GetObj3dDatas().find(names[0]) !=
          gameObjectManager_->GetObj3dDatas().end()) {
         enemys_.resize(enemyCount_ + 1);

         shared_ptr<GunEnemy> core = nullptr;
         core = make_shared<GunEnemy>();
         core->INameable::SetName(names[0]);
         core->Initialize();
         core->SetEnemyNumber(enemyCount_);

         enemys_[enemyCount_].parts.resize(enemys_[enemyCount_].partsSize);

         for (size_t i = 0; i < enemys_[enemyCount_].partsSize; i++) {
            shared_ptr<GunEnemyPart> parts = make_shared<GunEnemyPart>();
            parts->INameable::SetName(names[i + 1]);
            parts->Initialize();
            parts->SetEnemyNumber(enemyCount_);
            parts->SetIsCoreEnd(core->GetIsEnd());
            parts->SetIsUseGravityFlag(false);

            enemys_[enemyCount_].parts[i] = move(parts);
            objDataList_.push_back(enemys_[enemyCount_].parts[i]);
         }

         enemys_[enemyCount_].core = move(core);
         objDataList_.push_back(enemys_[enemyCount_].core);

         enemyCount_++;
      }
      else {
         break;
      }
   }
}

void GunEnemyManager::Update()
{
   if (*isGameStartFlag_ && !isSpeedSetFlag_) {
      for (auto &enemy : enemys_) {
         if (enemy.core) {
            enemy.core->SetVelocity({0.1f, 0.0f, 0.0f});
         }
      }
      isSpeedSetFlag_ = true;
   }

   for (auto &enemy : enemys_) {
      if (enemy.core) {
         enemy.core->Update();
         for (auto &parts : enemy.parts) {
            parts->Update();
         }

         // 死んだら消す
         if (enemy.core->GetIsDead()) {
            gameObjectManager_->ClearObj3dData(enemy.core->INameable::GetName());
            for (auto &parts : enemy.parts) {

               gameObjectManager_->ClearObj3dData(parts->INameable::GetName());
            }

            for (shared_ptr<GunEnemyBullet> &b : enemy.core->GetBullets()) {
               if (!b) {
                  continue;
               }

               gameObjectManager_->ClearObj3dData(b->INameable::GetName());
               b.reset();
            }

            enemy.Reset();
         }
      }
   }
}
