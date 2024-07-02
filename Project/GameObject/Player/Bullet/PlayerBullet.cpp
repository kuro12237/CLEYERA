#include "PlayerBullet.h"

void PlayerBullet::Initialize()
{
	state_ = make_unique<PlayerBulletStateNone>();
	state_->Initialize(this);

	name_ = "PlayerBullet";
	transform_.scale = { 1.0f,1.0f,1.0f };
	transform_.translate = spownPos_;
	SetObjectData(transform_);

	float velocityXZ = sqrt(pow(velocity_.x, 2.0f) + pow(velocity_.z, 2.0f));
	float height = -velocity_.y;
	Math::Vector::Vector3 rotate = {};
	rotate.y = std::atan2(velocity_.x, velocity_.z);
	rotate.x = std::atan2(height, velocityXZ);
	transform_.rotate = rotate;

	velocity_ = Math::Vector::Multiply(velocity_, { speed_,speed_,speed_ });
	id_ = kPlayerBullet;
	aabb_ = { {-0.1f,-0.1f,-0.1f,},{0.1f,0.1f,0.1f} };
}

void PlayerBullet::Update()
{
	state_->Update(this);

	timer_++;
	if (timer_ >= 360) {
		isDead_ = true;
	}

	transform_.translate = Math::Vector::Add(transform_.translate, velocity_);
	transform_.translate = Math::Vector::Add(transform_.translate, playerSpeed_);
}

void PlayerBullet::OnCollision(ICollider* c)
{
	c;

	if (c->GetId() == kPlayerId)
	{
		return;
	}
	isDead_ = true;
}
