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
	if (CheckBottomCollsion(theta))
	{
		//下
		if (a->GetIsExtrusionFlag())
		{
			a->PushBackHitDirection(BOTTOM);
			float extrusionA = BottomExtrusion(a, b);
			a->SetExtrusion({ 0,extrusionA });
		}
		//上
		if (b->GetIsExtrusionFlag())
		{
			b->PushBackHitDirection(TOP);
			float extrusionB = TopExtrusion(a, b);
			b->SetExtrusion({ 0,extrusionB });
		}
	}

	//上
	if (CheckTopCollision(theta))
	{
		//上
		if (a->GetIsExtrusionFlag())
		{
			a->PushBackHitDirection(TOP);
			float extrusionA = TopExtrusion(a, b);
			a->SetExtrusion({ 0,extrusionA });
		}
		//下
		if (b->GetIsExtrusionFlag())
		{
			b->PushBackHitDirection(BOTTOM);
			float extrusionB = BottomExtrusion(a, b);
			b->SetExtrusion({ 0,extrusionB });
		}
	}

	//左
	if (CheckLeftCollision(theta))
	{
		//左
		if (a->GetIsExtrusionFlag())
		{
			a->PushBackHitDirection(LEFT);
			float extrusionA = RightExtrusion(a, b);
			a->SetExtrusion({ extrusionA,0.0f });
		}
		//右
		if (b->GetIsExtrusionFlag())
		{
			b->PushBackHitDirection(RIGHT);
			float extrusionB = LeftExtrusion(a, b);
			b->SetExtrusion({ extrusionB,0.0f });
		}
	}
	//右
	if (CheckRightCollision(theta))
	{
		//右
		if (a->GetIsExtrusionFlag())
		{
			a->PushBackHitDirection(RIGHT);
			float extrusionA = LeftExtrusion(a, b);
			a->SetExtrusion({ extrusionA,0.0f });
		}
		//左
		if (b->GetIsExtrusionFlag())
		{
			b->PushBackHitDirection(LEFT);
			float extrusionB = RightExtrusion(a, b);
			b->SetExtrusion({ extrusionB,0.0f });
		}
	}

}

