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

			AABB a = colliderA->GetAABB();
			AABB b = colliderB->GetAABB();

			if (IsCollision(a,b))
			{
				colliderA->OnCollision(colliderB);
				colliderB->OnCollision(colliderA);
			}

		}
	}

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

