#pragma once
#include "GameObject/ObjectInterface/ObjectComponent.h"
#include "Graphics/CallPipline/PipelineHandler.h"
#include "Input.h"
#include "Particle/GoalParticle.h"
#include "STransformEular.h"
#include "Utility/ObjectId/GameObjectId.h"

/// <summary>
/// ゴールクラス
/// </summary>
class Goal : public ObjectComponent
{
 public:
   Goal() {};
   ~Goal() {};

   /// <summary>
   /// 初期化
   /// </summary>
   void Initialize() override;

   /// <summary>
   /// 更新
   /// </summary>
   void Update() override;

   /// <summary>
   /// 当たった時
   /// </summary>
   /// <param name="c"></param>
   void OnCollision(ObjectComponent *objData) override;

#pragma region Get
   bool GetIsGoalFlag() { return isGoalFlag_; }
#pragma endregion

#pragma region Set
   void SetGoalParticle(weak_ptr<GoalParticle> particle) { goalParticle_ = particle; }

   void SetGoalIndex(uint32_t index) { index_ = index; }
   void SetGoalObjectId(uint32_t id) { ObjectComponent::collider_->SetId(id); }
#pragma endregion

 private:
   string portalName_ = "GoalPortal";
   string backName_ = "GoalBack";

   bool isGoalFlag_ = false;
   uint32_t index_ = 0;

   weak_ptr<GoalParticle> goalParticle_;
};