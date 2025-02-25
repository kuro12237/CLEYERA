#pragma once
#include "GameObject/ObjectInterface/ObjectComponent.h"
#include "Pch.h"
#include "STransformEular.h"

#include "Input.h"
#include "Utility/ObjectId/GameObjectId.h"

#include "state/EnemyWalkStateDead.h"
#include "state/EnemyWalkStateMove.h"
#include "state/IEnemyWalkState.h"

#include"GameObject/Particles/CharacterDeadParticle.h"

/// <summary>
/// 歩く敵
/// </summary>
class EnemyWalk : public ObjectComponent
{
 public:
   EnemyWalk() {};
   ~EnemyWalk() {};

   /// <summary>
   /// 初期化
   /// </summary>
   void Initialize();

   /// <summary>
   /// 更新
   /// </summary>
   void Update();

   /// <summary>
   /// 当たった時
   /// </summary>
   void OnCollision(ObjectComponent *objData) override;

   /// <summary>
   /// 状態遷移
   /// </summary>
   /// <param name="state"></param>
   void ChangeState(unique_ptr<IEnemyWalkState> state);

#pragma region Get
   bool &GetIsHit() { return isHit_; }
   bool &GetIsDead() { return isDead_; }
   bool &GetIsEnd() { return isEnd_; }
   Math::Vector::Vector3 GetImpactDirection() { return impactDirection_; }

   weak_ptr<CharacterDeadParticle> GetDeadParticle() { return deadParticle_; }
#pragma endregion

#pragma region Set

   void SetDeadParticle(const weak_ptr<CharacterDeadParticle> &particle)
   {
      deadParticle_ = particle;
   }

#pragma endregion

 private:
   bool isHit_ = false;
   bool isDead_ = false;
   bool isEnd_ = false;

   unique_ptr<IEnemyWalkState> state_ = nullptr;

   Math::Vector::Vector3 impactDirection_ = {};

   weak_ptr<CharacterDeadParticle> deadParticle_;
};
