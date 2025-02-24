#include "EnemyWalkManager.h"

void EnemyWalkManager::Initialize()
{
   gameObjectManager_ = GameObjectManager::GetInstance();

   const string name = "EnemyWalk";

   for (uint32_t Count_ = 0; Count_ < uint32_t(gameObjectManager_->GetObj3dDatas().size());
        Count_++) {
      string count = to_string(enemyCount_);

      string enemyName = "";
      if (count == "0") {
         enemyName = name;
      }
      else {
         enemyName =
             name + "." + string(3 - to_string(enemyCount_).length(), '0') + to_string(enemyCount_);
      }

      if (gameObjectManager_->GetObj3dDatas().find(enemyName) !=
          gameObjectManager_->GetObj3dDatas().end()) {
         auto obj = gameObjectManager_->GetObj3dData(enemyName);

         shared_ptr<EnemyWalk> enemyWalk = nullptr;
         enemyWalk = make_shared<EnemyWalk>();
         enemyWalk->INameable::SetName(enemyName);
         enemyWalk->Initialize();

         enemys_.resize(enemyCount_ + 1);
         enemys_[enemyCount_] = (enemyWalk);
         objDataList_.push_back(enemys_[enemyCount_]);
         enemyCount_++;
      }
      else {
         break;
      }
   }
}

void EnemyWalkManager::Update()
{
   if (*isGameStartFlag_&&!isSpeedSetFlag_) {
      for (auto &enemy : enemys_) {
         if (enemy) {
            enemy->SetVelocity({0.1f, 0.0f, 0.0f});
         }
      }
      isSpeedSetFlag_ = true;
   }
   for (auto &enemy : enemys_) {
      if (enemy) {
         enemy->Update();
         // ���񂾂����
         if (enemy->GetIsEnd()) {
            GameObjectManager::GetInstance()->ClearObj3dData(enemy->INameable::GetName());
            enemy.reset();
         }
      }
   }
}

void EnemyWalkManager::SetDeadParticle(const weak_ptr<CharacterDeadParticle> &p) 
{
   for (auto &enemy : enemys_) {
      if (enemy) {
          enemy->SetDeadParticle(p);
      }
   }

}
