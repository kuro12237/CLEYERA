#include "GunEnemyPart.h"

void GunEnemyPart::Initialize()
{
   AABB aabb = {.min = {-1.0f, -1.0f, -1.0f}, .max = {1.0f, 1.0f, 1.0f}};
   // dataをセット
   objectData_ = gameObjectManager_->GetObj3dData(INameable::name_);

   // コライダーセット
   this->SetColliderParamData();
   collider_->SetAABB(aabb);
   collider_->SetId(ObjectId::kGunEnemyId);
   collider_->SetIsExtrusion(true);
   collider_->SetMask(CollisionMask::kEnemyWalkMask);
   collider_->SetAttribute(CollisionMask::kEnemyWalkAttribute);
}

void GunEnemyPart::Update()
{
   if (*isCoreEnd_ && !isEnd_) {
      collider_->SetId(ObjectId::kOnlyCollideWithBlocksid);
      isUseGravityFlag_ = true;
      ChangeState(make_unique<GunEnemyStateDeadAnimation>());
      isEnd_ = *isCoreEnd_;
   }

   if (state_) {
      state_->Update(this);
   }

   auto &transform = objectData_.lock()->GetWorldTransform().transform;
   transform.translate.x += velocity_.x;
   transform.translate.y += velocity_.y;

   collider_->ClearExtrusion();
   collider_->ClearHitDirection();
}

void GunEnemyPart::OnCollision([[maybe_unused]] ObjectComponent *objData)
{
   auto c = objData->GetCollider();

   { // 敵同士の処理
      if (ObjectId::kEnemyWalkId == c->GetId()) {
         return;
      }
   }
   // ブロックとの処理
   if (ObjectId::kNormalBlock == c->GetId()) {
      for (auto &hitDirection : collider_->GetHItDirection()) {
         if (hitDirection == TOP) {
            velocity_.y = 0.0f;
         }
         if (hitDirection == BOTTOM && velocity_.y <= 0.0f) {
            velocity_.y = 0.0f;
         }
         if (hitDirection == LEFT || hitDirection == RIGHT) {
            velocity_.x *= -1.0f;
         }
      }

      auto &transform = objectData_.lock()->GetWorldTransform().transform;

      transform.translate.x += collider_->GetExtrusion().x;
      transform.translate.y += collider_->GetExtrusion().y;
   }
}
