#include "EnemyWalk.h"

void EnemyWalk::Initialize()
{
	SetName("EnemyWalk");
	SetObjectData(this->transform_);
	aabb_ = { { -1.0f,-1.0f,-1.0f }, { 1.0f,1.0f,1.0f } };
	isExtrusion_ = true;
	id_ = kEnemyWalkId;
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

	if (kNormalBlock == c->GetId()) {
		for (auto& hitDirection : hitDirection_)
		{
			if (hitDirection == TOP)
			{
				velocity_ = {};
			}
			if (hitDirection == BOTTOM && velocity_.y <= 0.0f)
			{
				velocity_ = {};
			}
		}
		transform_.translate.x += extrusion_.x;
		transform_.translate.y += extrusion_.y;
	}
}
