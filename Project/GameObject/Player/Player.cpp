#include "Player.h"

void Player::Initialize()
{
	SetName("Player");
	SetObjectData(this->transform_);
	this->isExtrusion_ = true;
}

void Player::Update()
{
	//“–‚½‚è”»’è
	ClearExtrusion();
	ClearHitDirection();

	if (Input::GetInstance()->PushKey(DIK_W))
	{
		transform_.translate.y += 0.1f;
	}
	if (Input::GetInstance()->PushKey(DIK_S))
	{
		transform_.translate.y -= 0.1f;
	}
	if (Input::GetInstance()->PushKey(DIK_D))
	{
		transform_.translate.x += 0.1f;
	}
	if (Input::GetInstance()->PushKey(DIK_A))
	{
		transform_.translate.x -= 0.1f;
	}
}

void Player::OnCollision(ICollider* c)
{
	c;
	transform_.translate.x += extrusion_.x;
	transform_.translate.y += extrusion_.y;
	LogManager::Log("HitPlayer\n");
}
