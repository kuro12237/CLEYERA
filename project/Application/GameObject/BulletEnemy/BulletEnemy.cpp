#include "BulletEnemy.h"

void BulletEnemy::Initialize()
{
	auto& transform = gameObjectManager_->GetObj3dData(INameable::name_)->GetWorldTransform().transform;
	SetObjectData(transform);

	Math::Vector::Vector2 minmax = { -1.0f,1.0f };
	aabb_ = { Math::Vector::Multiply(transform.scale,minmax.x), Math::Vector::Multiply(transform.scale,minmax.y) };
	isExtrusion_ = true;
	id_ = kEnemyWalkId;
	attribute_ = CollisionMask::kEnemyWalkAttribute;
	mask_ = CollisionMask::kEnemyWalkMask;

}

void BulletEnemy::Update()
{
	ClearExtrusion();
	ClearHitDirection();
	IsHit_ = false;
}

void BulletEnemy::OnCollision(ICollider* c, IObjectData* objData)
{
	objData;
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
			if (!isDead_)
			{
				isDead_ = true;
				gameObjectManager_->SetObjectPipline(make_unique<Phong3dDissolvePipline>(), INameable::name_);
		
			}
		}

		if (kPlayerId == c->GetId())
		{
			if (!isDead_)
			{
				isDead_ = true;
				gameObjectManager_->SetObjectPipline(make_unique<Phong3dDissolvePipline>(), INameable::name_);

			}
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
		auto& transform = gameObjectManager_->GetObj3dData(INameable::name_)->GetWorldTransform().transform;
		transform.translate.x += extrusion_.x;
		transform.translate.y += extrusion_.y;
	}

}
