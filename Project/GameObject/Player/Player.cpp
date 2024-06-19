#include "Player.h"

void Player::Initialize()
{
	SetName("Player");
	transform_;

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
	transform_;
}
