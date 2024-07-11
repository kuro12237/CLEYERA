#include "EnemyWalk.h"

void EnemyWalk::Initialize()
{
	SetName("EnemyWalk");
	SetObjectData(this->transform_);
	aabb_ = { { -1.0f,-1.0f,-1.0f }, { 1.0f,1.0f,1.0f } };
	isExtrusion_ = true;
	id_ = kEnemyWalkId;

	state_ = make_unique<EnemyWalkStateMove>();
	state_->Initialize();
}

void EnemyWalk::Update()
{
	state_->Update(this);

	ClearExtrusion();
	ClearHitDirection();
	IsHit_ = false;
}

void EnemyWalk::OnCollision(ICollider* c)
{
	c;
	IsHit_ = true;

	if (kPlayerBullet ==c->GetId())
	{
		isDead_ = true;
	}

	if (kPlayerId == c->GetId())
	{

		isDead_ = true;
	}

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
			if (hitDirection == LEFT)
			{
			   speed_ *= -1.0f;
			}
		}
		transform_.translate.x += extrusion_.x;
		transform_.translate.y += extrusion_.y;
	}
}
