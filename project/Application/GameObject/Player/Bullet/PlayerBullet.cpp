#include "PlayerBullet.h"

void PlayerBullet::Initialize(string number)
{
	state_ = make_unique<PlayerBulletStateNone>();
	state_->Initialize(this);

	name_ = number;
	auto& transform = GameObjectManager::GetInstance()->GetObj3dData(name_)->GetWorldTransform().transform;
	transform.scale = { 1.0f,1.0f,1.0f };
	transform.translate = spownPos_;
	SetObjectData(transform);

	//��]�K�p
	float velocityXZ = sqrt(pow(velocity_.x, 2.0f) + pow(velocity_.z, 2.0f));
	float height = -velocity_.y;
	Math::Vector::Vector3 rotate = {};
	rotate.y = std::atan2(velocity_.x, velocity_.z);
	rotate.x = std::atan2(height, velocityXZ);
	transform.rotate = rotate;

	velocity_ = Math::Vector::Multiply(velocity_, { speed_,speed_,speed_ });
	id_ = kPlayerBullet;
	aabb_ = { {-0.1f,-0.1f,-0.1f,},{0.1f,0.1f,0.1f} };
	attribute_ = CollisionMask::kPlayerBulletAttribute;
	mask_ = CollisionMask::kPlayerBulletMask;
}

void PlayerBullet::Update()
{
	state_->Update(this);

	timer_++;
	if (timer_ >= timerMax_) {
		isDead_ = true;
	}

	auto& transform = GameObjectManager::GetInstance()->GetObj3dData(name_)->GetWorldTransform().transform;
	transform.translate = Math::Vector::Add(transform.translate, velocity_);

}

void PlayerBullet::OnCollision(ICollider* c)
{
	if (c->GetId() == kOnlyCollideWithBlocksid)
	{
		return;
	}
	if (c->GetId() == kPlayerId)
	{
		return;
	}
	isDead_ = true;
}
