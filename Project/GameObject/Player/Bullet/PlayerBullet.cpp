#include "PlayerBullet.h"

void PlayerBullet::Initialize()
{
	state_ = make_unique<PlayerBulletStateNone>();
	state_->Initialize(this);

	transform_.scale = { 1.0f,1.0f,1.0f };
	SetTransform(transform_);
	transform_.translate = spownPos_;
	velocity_ = Math::Vector::Multiply(velocity_, { speed_,speed_,speed_ });
}

void PlayerBullet::Update()
{
	state_->Update(this);

	timer_++;
	if (timer_ >= 360) {
		isDead_ = true;
	}

	transform_.translate = Math::Vector::Add(transform_.translate, velocity_);
}
