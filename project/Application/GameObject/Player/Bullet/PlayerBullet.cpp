#include "PlayerBullet.h"

void PlayerBullet::Initialize()
{
   state_ = make_unique<PlayerBulletStateNone>();
   state_->Initialize(this);

   // dataをセット
   objectData_ = gameObjectManager_->GetObj3dData(INameable::name_);

   auto &transform = objectData_.lock()->GetWorldTransform().transform;

   transform.scale = {1.0f, 1.0f, 1.0f};
   transform.translate = spownPos_;

   // 回転適用
   float velocityXZ = sqrt(pow(velocity_.x, 2.0f) + pow(velocity_.z, 2.0f));
   float height = -velocity_.y;
   Math::Vector::Vector3 rotate = {};
   rotate.y = std::atan2(velocity_.x, velocity_.z);
   rotate.x = std::atan2(height, velocityXZ);
   transform.rotate = rotate;

   velocity_ = Math::Vector::Multiply(velocity_, {speed_, speed_, speed_});
   const AABB aabb = {{-0.1f,-0.1f,-0.1f,},
                      {0.1f, 0.1f, 0.1f}};

   // コライダーセット
   this->SetColliderParamData();
   collider_->SetAABB(aabb);
   collider_->SetId(ObjectId::kPlayerBullet);
   collider_->SetIsExtrusion(false);
   collider_->SetMask(CollisionMask::kPlayerBulletMask);
   collider_->SetAttribute(CollisionMask::kPlayerBulletAttribute);
   isUseGravityFlag_ = false;
}

void PlayerBullet::Update()
{
   state_->Update(this);

   timer_++;
   if (timer_ >= timerMax_) {
      isDead_ = true;
   }

   auto &transform = GameObjectManager::GetInstance()
                         ->GetObj3dData(INameable::name_)
                         ->GetWorldTransform()
                         .transform;
   transform.translate = Math::Vector::Add(transform.translate, velocity_);
}

void PlayerBullet::OnCollision([[maybe_unused]] ObjectComponent *objData)
{
   auto c = objData->GetCollider();

   if (c->GetId() == ObjectId::kOnlyCollideWithBlocksid) {
      return;
   }
   if (c->GetId() == ObjectId::kPlayerId) {
      return;
   }
   isDead_ = true;
}
