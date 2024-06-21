#pragma once
#include"ICollider.h"

class BoxCollisionManager
{
public:
	BoxCollisionManager() {};
	~BoxCollisionManager() {};

	void ListClear();

	void ListPushback(ICollider* c);

	void CheckAllCollisoin();



private:

	bool IsCollision(const AABB& aabb1, const AABB& aabb2);

	list<ICollider*>colliders_;

};

