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

	{//�G���m�̏���
		if (kEnemyWalkId == c->GetId())
		{
			speed_ *= -1.0f;
		}
	}

	{//�v���C���[�Ƃ̏���
		if (kPlayerBullet == c->GetId())
		{
			isDead_ = true;
		}

		if (kPlayerId == c->GetId())
		{

			isDead_ = true;
		}
	}

	//�u���b�N�Ƃ̏���
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
