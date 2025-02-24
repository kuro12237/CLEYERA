#pragma once
#include "EnemyWalk.h"
#include "GameObject/ObjectInterface/ManagerComponent.h"
#include "Utility/ObjectManager/GameObjectManager.h"

/// <summary>
/// 歩く敵の管理クラス
/// </summary>
class EnemyWalkManager : public ManagerComponent
{
 public:
   EnemyWalkManager() {};
   ~EnemyWalkManager() {};

   /// <summary>
   /// 初期化
   /// </summary>
   /// <param name="data"></param>
   void Initialize() override;

   /// <summary>
   /// 更新
   /// </summary>
   void Update() override;

#pragma region Get
   vector<shared_ptr<EnemyWalk>> GetData() { return enemys_; }
#pragma endregion

#pragma region Set
   void SetDeadParticle(const weak_ptr<CharacterDeadParticle> &p);

#pragma endregion

 private:
   GameObjectManager *gameObjectManager_ = nullptr;

   uint32_t enemyCount_ = 0;
   vector<shared_ptr<EnemyWalk>> enemys_;
   bool isSpeedSetFlag_ = false;
};
