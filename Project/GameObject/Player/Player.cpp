#include "Player.h"

void Player::Initialize()
{
	SetName("Player");
	SetObjectData(this->transform_);
}

void Player::Update()
{

	if (Input::GetInstance()->PushKey(DIK_W))
	{
		transform_.translate.y += 0.1f;
	}
	if (Input::GetInstance()->PushKey(DIK_S))
	{
		transform_.translate.y -= 0.1f;
	}
}

void Player::OnCollision(ICollider* c)
{
	c;
}
