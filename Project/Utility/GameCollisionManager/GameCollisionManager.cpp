#include "GameCollisionManager.h"

void GameCollisonManager::CheckAllCollisions()
{

	list<IBoxCollider*>::iterator itrA = colliders_.begin();

	for (; itrA != colliders_.end(); ++itrA) {

		IBoxCollider* colliderA = *itrA;
		list<IBoxCollider*>::iterator itrB = itrA;
		itrB++;
		for (; itrB != colliders_.end(); ++itrB) {
			IBoxCollider* colliderB = *itrB;

			AABB a = SettingAABBParam(colliderA);
			AABB b = SettingAABBParam(colliderB);

			extrusionXY_A = {};
			extrusionXY_B = {};

			//判定
			// コリジョンフィルタリング
			if ((colliderA->GetAttbute() & colliderB->GetMask()) == 0 ||
				(colliderA->GetMask() & colliderB->GetAttbute()) == 0)
			{
				return;
			}
			if (IsCollision(a, b))
			{

				colliderA->ClearFlag();
				colliderB->ClearFlag();

				//方向を出して押し出し計算
				CheckExtrusion(colliderA, colliderB);

				colliderA->SetExtrusion(extrusionXY_A);
				colliderB->SetExtrusion(extrusionXY_B);

				colliderA->OnCollision(colliderB);
				colliderB->OnCollision(colliderA);
			}
			else
			{
				colliderA->SetExtrusion({});
				colliderB->SetExtrusion({});
			}
		}
	}
}

bool GameCollisonManager::CheckBottomCollsion(float t)
{
	if (t >= (std::numbers::pi / 3.5f) && t <= std::numbers::pi - (std::numbers::pi / 3.5f)) {
		return true;
	}
	return false;
}

bool GameCollisonManager::CheckTopCollision(float t)
{
	if (t <= -(std::numbers::pi / 3.5f) && t >= -std::numbers::pi + (std::numbers::pi / 3.5f))
	{
		return true;
	}
	return false;
}

bool GameCollisonManager::CheckLeftCollision(float t)
{
	if (t < std::numbers::pi / 4.0f && t > -(std::numbers::pi / 4.0f))
	{
		return true;
	}
	return false;
}

bool GameCollisonManager::CheckRightCollision(float t)
{
	if (t > std::numbers::pi - (std::numbers::pi / 4.5f) || t < -std::numbers::pi + (std::numbers::pi / 4.5f))
	{
		return true;
	}
	return false;
}

bool GameCollisonManager::IsCollision(const AABB& aabb1, const AABB& aabb2)
{

	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&
		(aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&
		(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z)
		) {
		return true;
	}
	return false;
}

float GameCollisonManager::BottomExtrusion(IBoxCollider* a, IBoxCollider* b)
{
	return (-a->GetAABB().min.y + b->GetAABB().max.y) - (a->GetWorldPosition().y - b->GetWorldPosition().y);
}

float GameCollisonManager::TopExtrusion(IBoxCollider* a, IBoxCollider* b)
{
	return (a->GetAABB().max.y + -b->GetAABB().min.y) - (b->GetWorldPosition().y - a->GetWorldPosition().y);
}

float GameCollisonManager::RightExtrusion(IBoxCollider* a, IBoxCollider* b)
{
	return (-a->GetAABB().min.x + b->GetAABB().max.x) - (a->GetWorldPosition().x - b->GetWorldPosition().x);
}

float GameCollisonManager::LeftExtrusion(IBoxCollider* a, IBoxCollider* b)
{
	return (a->GetAABB().max.x + -b->GetAABB().min.x) - (b->GetWorldPosition().x - a->GetWorldPosition().x);
}

void GameCollisonManager::CheckExtrusion(IBoxCollider* a, IBoxCollider* b)
{
	float theta = atan2(a->GetWorldPosition().y - b->GetWorldPosition().y, a->GetWorldPosition().x - b->GetWorldPosition().x);
	//下
	if (CheckBottomCollsion(theta))
	{
		//めり込み度の算出
		a->HitBottom(true);
		float extrusionA = BottomExtrusion(a, b);
		extrusionXY_A.y = extrusionA;

		b->HitTop(true);
		float ExtrusionB = TopExtrusion(a, b);
		extrusionXY_B.y = ExtrusionB * -1;
	}
	//else { a->HitBottom(false); /*b->HitTop(false);*/ }
	//上
	if (CheckTopCollision(theta))
	{
		//めり込み度の算出
		a->HitTop(true);
		float extrusionA = TopExtrusion(a, b);
		extrusionXY_A.y = extrusionA * -1;

		b->HitBottom(true);
		float extrusionB = BottomExtrusion(a, b);
		extrusionXY_B.y = extrusionB;
	}
	//else { a->HitTop(false); /*b->HitBottom(false); */}

	//左
	if (CheckLeftCollision(theta))
	{
		//めり込み度の算出
		a->HitLeft(true);
		float extrusionA = RightExtrusion(a, b);
		extrusionXY_A.x = extrusionA;

		b->HitRight(true);
		float extrusionB = LeftExtrusion(a, b);
		extrusionXY_B.x = extrusionB * -1;

	}
	//else { a->HitLeft(false); /*b->HitRight(false); */}

	//右
	if (CheckRightCollision(theta))
	{
		//めり込み度の算出
		a->HitRight(true);
		float extrusionA = LeftExtrusion(a, b);
		extrusionXY_A.x = extrusionA * -1;

		b->HitLeft(true);
		float extrusionB = RightExtrusion(a, b);
		extrusionXY_B.x = extrusionB;
	}
	//else { a->HitRight(false); /*b->HitLeft(false);*/ }

}

AABB GameCollisonManager::SettingAABBParam(IBoxCollider* c)
{

	AABB result{};

	result.min = {
		.x = c->GetWorldPosition().x + (c->GetAABB().min.x),
		.y = c->GetWorldPosition().y + (c->GetAABB().min.y),
		.z = c->GetWorldPosition().z + (c->GetAABB().min.z),
	};
	result.max = {
		.x = c->GetWorldPosition().x + (c->GetAABB().max.x),
		.y = c->GetWorldPosition().y + (c->GetAABB().max.y),
		.z = c->GetWorldPosition().z + (c->GetAABB().max.z),
	};

	return result;
}