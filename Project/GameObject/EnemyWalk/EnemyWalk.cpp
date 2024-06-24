#include "EnemyWalk.h"

void EnemyWalk::Initialize()
{
	SetName("EnemyWalk");
	SetObjectData(this->transform_);
	aabb_ = { { -1.0f,-1.0f,-1.0f }, { 1.0f,1.0f,1.0f } };
}

void EnemyWalk::Update()
{
	ClearExtrusion();
	ClearHitDirection();

	if (Input::GetInstance()->PushKey(DIK_UP))
	{
		transform_.translate.y += 0.1f;
	}
	if (Input::GetInstance()->PushKey(DIK_DOWN))
	{
		transform_.translate.y -= 0.1f;
	}
	if (Input::GetInstance()->PushKey(DIK_RIGHT))
	{
		transform_.translate.x += 0.1f;
	}
	if (Input::GetInstance()->PushKey(DIK_LEFT))
	{
		transform_.translate.x -= 0.1f;
	}
}

void EnemyWalk::OnCollision(ICollider* c)
{
	c;

	transform_.translate.x += extrusion_.x;
	transform_.translate.y += extrusion_.y;
}
