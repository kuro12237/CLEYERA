#include "EnemyWalk.h"

void EnemyWalk::Initialize()
{
   auto &transform =
       gameObjectManager_->GetObj3dData(INameable::name_)->GetWorldTransform().transform;

   Math::Vector::Vector2 minmax = {-1.0f, 1.0f};
   AABB aabb = {Math::Vector::Multiply(transform.scale, minmax.x),
                Math::Vector::Multiply(transform.scale, minmax.y)};

   // dataをセット
   objectData_ = gameObjectManager_->GetObj3dData(INameable::name_);

   // コライダーセット
   this->SetColliderParamData();
   collider_->SetAABB(aabb);
   collider_->SetId(ObjectId::kEnemyWalkId);
   collider_->SetIsExtrusion(true);
   collider_->SetMask(CollisionMask::kEnemyWalkMask);
   collider_->SetAttribute(CollisionMask::kEnemyWalkAttribute);

   state_ = make_unique<EnemyWalkStateMove>();
   state_->Initialize(this);
}

void EnemyWalk::Update()
{
   state_->Update(this);

   auto &transform = objectData_.lock()->GetWorldTransform().transform;
   transform.translate.x += velocity_.x;
   transform.translate.y += velocity_.y;

   collider_->ClearExtrusion();
   collider_->ClearHitDirection();
   isHit_ = false;
}

void EnemyWalk::OnCollision([[maybe_unused]] ObjectComponent *objData)
{
   isHit_ = true;
   auto c = objData->GetCollider();

   { // 敵同士の処理
      if (ObjectId::kEnemyWalkId == c->GetId()) {
         velocity_.x *= 1.0f;
      }
   }

   { // プレイヤーとの処理
      if (ObjectId::kPlayerBullet == c->GetId()) {
         if (!isDead_) {
            impactDirection_ = objData->GetVelocity();
            isDead_ = true;
            gameObjectManager_->SetObjectPipline(make_unique<Phong3dDissolvePipline>(),
                                                 INameable::name_);
            ChangeState(make_unique<EnemyWalkStateDead>());
         }
      }

      if (ObjectId::kPlayerId == c->GetId()) {
         if (!isDead_) {
            isDead_ = true;
            gameObjectManager_->SetObjectPipline(make_unique<Phong3dDissolvePipline>(),
                                                 INameable::name_);
            ChangeState(make_unique<EnemyWalkStateDead>());
         }
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

void EnemyWalk::ChangeState(unique_ptr<IEnemyWalkState> state)
{
   state_.release();
   state_ = move(state);
   state_->Initialize(this);
}
