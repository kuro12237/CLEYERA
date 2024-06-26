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

	AABB SettingAABBParam(ICollider* c);
	bool IsCollision(const AABB& aabb1, const AABB& aabb2);

	//élï˚å¸ÇÃîªíË
	bool CheckBottomCollsion(float t);
	bool CheckTopCollision(float t);
	bool CheckLeftCollision(float t);
	bool CheckRightCollision(float t);

	//âüÇµèoÇµ
	float BottomExtrusion(ICollider* a, ICollider* b);
	float TopExtrusion(ICollider* a, ICollider* b);
	float RightExtrusion(ICollider* a, ICollider* b);
	float LeftExtrusion(ICollider* a, ICollider* b);

	void CheckExtrusion(ICollider* a, ICollider* b);
	list<ICollider*>colliders_;


};

