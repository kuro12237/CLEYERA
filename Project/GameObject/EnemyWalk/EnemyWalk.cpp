#include "EnemyWalk.h"

void EnemyWalk::Initialize()
{
	auto& transform = GameObjectManager::GetInstance()->GetObj3dData(name_)->GetWorldTransform().transform;
	SetObjectData(transform);
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
	IsHit_ = true;

	{//敵同士の処理
		if (kEnemyWalkId == c->GetId())
		{
			speed_ *= -1.0f;
		}
	}

	{//プレイヤーとの処理
		if (kPlayerBullet == c->GetId())
		{
			isDead_ = true;
		}

		if (kPlayerId == c->GetId())
		{

			isDead_ = true;
		}
	}

	//ブロックとの処理
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
			if (hitDirection == LEFT || hitDirection == RIGHT)
			{
				speed_ *= -1.0f;
			}
		}
		auto& transform = GameObjectManager::GetInstance()->GetObj3dData(name_)->GetWorldTransform().transform;
		transform.translate.x += extrusion_.x;
		transform.translate.y += extrusion_.y;
	}
}
