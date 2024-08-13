#include "EnemyWalk.h"

void EnemyWalk::Initialize()
{
	gameObjIncetance_ = GameObjectManager::GetInstance();
	auto& transform = gameObjIncetance_->GetObj3dData(name_)->GetWorldTransform().transform;
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
			if (!isDead_)
			{
				isDead_ = true;
				gameObjIncetance_->SetObjectPipline(make_unique<Phong3dDissolvePipline>(), name_);
				ChangeState(make_unique<EnemyWalkStateDead>());
			}
		}

		if (kPlayerId == c->GetId())
		{
			if (!isDead_)
			{
				isDead_ = true;
				gameObjIncetance_->SetObjectPipline(make_unique<Phong3dDissolvePipline>(), name_);
				ChangeState(make_unique<EnemyWalkStateDead>());
			}
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
		auto& transform = gameObjIncetance_->GetObj3dData(name_)->GetWorldTransform().transform;
		transform.translate.x += extrusion_.x;
		transform.translate.y += extrusion_.y;
	}
}

void EnemyWalk::ChangeState(unique_ptr<IEnemyWalkState> state)
{
	state_.release();
	state_ = move(state);
	state_->Initialize();
}
