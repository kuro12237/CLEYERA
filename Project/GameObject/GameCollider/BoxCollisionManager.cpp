#include "BoxCollisionManager.h"

void BoxCollisionManager::ListClear()
{
	colliders_.clear();
}

void BoxCollisionManager::ListPushback(ICollider* c)
{
	colliders_.push_back(c);
}

void BoxCollisionManager::CheckAllCollisoin()
{

	list<ICollider*>::iterator itrA = colliders_.begin();

	for (; itrA != colliders_.end(); ++itrA) {

		ICollider* colliderA = *itrA;
		list<ICollider*>::iterator itrB = itrA;
		itrB++;

		for (; itrB != colliders_.end(); ++itrB) {
			ICollider* colliderB = *itrB;

			AABB a = SettingAABBParam(colliderA);
			AABB b = SettingAABBParam(colliderB);

			if (IsCollision(a, b))
			{
				//めり込み計算
				colliderA->ClearExtrusion();
				colliderA->ClearHitDirection();

				CheckExtrusion(colliderA, colliderB);

				colliderA->OnCollision(colliderB);
				colliderB->OnCollision(colliderA);
			}
		}
	}

}

AABB BoxCollisionManager::SettingAABBParam(ICollider* c)
{
	AABB result{};
	result.min = {

		.x = c->GetpTransform().translate.x + (c->GetAABB().min.x),
		.y = c->GetpTransform().translate.y + (c->GetAABB().min.y),
		.z = c->GetpTransform().translate.z + (c->GetAABB().min.z),
	};
	result.max = {
		.x = c->GetpTransform().translate.x + (c->GetAABB().max.x),
		.y = c->GetpTransform().translate.y + (c->GetAABB().max.y),
		.z = c->GetpTransform().translate.z + (c->GetAABB().max.z),
	};

	return result;
}
bool BoxCollisionManager::IsCollision(const AABB& aabb1, const AABB& aabb2)
{
	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&
		(aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&
		(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z)
		) {
		return true;
	}
	return false;
}

bool BoxCollisionManager::CheckBottomCollsion(float t)
{
	if (t >= (std::numbers::pi / 3.5f) && t <= std::numbers::pi - (std::numbers::pi / 3.5f)) {
		return true;
	}
	return false;
}

bool BoxCollisionManager::CheckTopCollision(float t)
{
	if (t <= -(std::numbers::pi / 3.5f) && t >= -std::numbers::pi + (std::numbers::pi / 3.5f))
	{
		return true;
	}
	return false;
}

bool BoxCollisionManager::CheckLeftCollision(float t)
{
	if (t < std::numbers::pi / 4.0f && t > -(std::numbers::pi / 4.0f))
	{
		return true;
	}
	return false;
}

bool BoxCollisionManager::CheckRightCollision(float t)
{
	if (t > std::numbers::pi - (std::numbers::pi / 4.5f) || t < -std::numbers::pi + (std::numbers::pi / 4.5f))
	{
		return true;
	}
	return false;
}

float BoxCollisionManager::BottomExtrusion(ICollider* a, ICollider* b)
{
	return (-a->GetAABB().min.y + b->GetAABB().max.y) - (a->GetpTransform().translate.y - b->GetpTransform().translate.y);
}

float BoxCollisionManager::TopExtrusion(ICollider* a, ICollider* b)
{
	return (-a->GetAABB().max.y + b->GetAABB().min.y) - (a->GetpTransform().translate.y - b->GetpTransform().translate.y);
}

float BoxCollisionManager::RightExtrusion(ICollider* a, ICollider* b)
{
	return (-a->GetAABB().min.x + b->GetAABB().max.x) - (a->GetpTransform().translate.x - b->GetpTransform().translate.x);
}

float BoxCollisionManager::LeftExtrusion(ICollider* a, ICollider* b)
{
	return (-a->GetAABB().max.x + b->GetAABB().min.x) - (a->GetpTransform().translate.x - b->GetpTransform().translate.x);
}

void BoxCollisionManager::CheckExtrusion(ICollider* a, ICollider* b)
{
	float theta = atan2(a->GetpTransform().translate.y - b->GetpTransform().translate.y, a->GetpTransform().translate.x - b->GetpTransform().translate.x);
	//Aをもとにめり込み度を算出
	Math::Vector::Vector2 extrusionA = {};
	Math::Vector::Vector2 extrusionB = {};

	if (CheckBottomCollsion(theta))
	{
		//下
		if (a->GetIsExtrusionFlag())
		{
			a->PushBackHitDirection(BOTTOM);
			extrusionA.y = BottomExtrusion(a, b);
		}
		//上
		if (b->GetIsExtrusionFlag())
		{
			b->PushBackHitDirection(TOP);
			extrusionB.y = TopExtrusion(a, b);
		}
	}

	//上
	if (CheckTopCollision(theta))
	{
		//上
		if (a->GetIsExtrusionFlag())
		{
			a->PushBackHitDirection(TOP);
			extrusionA.y = TopExtrusion(a, b);
		}
		//下
		if (b->GetIsExtrusionFlag())
		{
			b->PushBackHitDirection(BOTTOM);
			extrusionB.y = BottomExtrusion(a, b);
		}
	}

	//左
	if (CheckLeftCollision(theta))
	{
		if (a->GetIsExtrusionFlag())
		{
			a->PushBackHitDirection(LEFT);
			extrusionA.x = RightExtrusion(a, b);
		}
		//右
		if (b->GetIsExtrusionFlag())
		{
			b->PushBackHitDirection(RIGHT);
			extrusionB.x = LeftExtrusion(a, b);
		}
	}
	//右
	if (CheckRightCollision(theta))
	{
		if (a->GetIsExtrusionFlag())
		{
			a->PushBackHitDirection(RIGHT);
			extrusionA.x = LeftExtrusion(a, b);
		}
		//左
		if (b->GetIsExtrusionFlag())
		{
			b->PushBackHitDirection(LEFT);
			extrusionB.x = RightExtrusion(a, b);
		}
	}
	a->SetExtrusion(extrusionA);
	b->SetExtrusion(extrusionB);
}

