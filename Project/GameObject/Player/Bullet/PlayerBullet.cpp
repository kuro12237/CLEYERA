#include "PlayerBullet.h"

void PlayerBullet::Initialize()
{
	state_ = make_unique<PlayerBulletStateNone>();
	state_->Initialize(this);

	name_ = "PlayerBullet";
	transform_.scale = { 1.0f,1.0f,1.0f };
	transform_.translate = spownPos_;
	SetObjectData(transform_);

	velocity_ = Math::Vector::Multiply(velocity_, { speed_,speed_,speed_ });
	id_ = kPlayerBullet;
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

void PlayerBullet::OnCollision(ICollider* c)
{
	c;

	if (c->GetId() == kPlayerId)
	{
		return;
	}
	isDead_ = true;
}
