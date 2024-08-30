#pragma once
#include"ICollider.h"

class BoxCollisionManager
{
public:
	BoxCollisionManager() {};
	~BoxCollisionManager() { End(); }

	void End();

	void ListPushback(ICollider* c);

	void CheckAllCollisoin();

private:

	void CollidersAllHitsIdsClear();
	void ListClear();

	float CalculateAngle(float x, float y);
	float NomalizeDegree(float theta);

	AABB SettingAABBParam(ICollider* c);
	bool IsCollision(const AABB& aabb1, const AABB& aabb2);

	//élï˚å¸ÇÃîªíË
	bool CheckBottomCollsion(float t,Math::Vector::Vector4 bDegree);
	bool CheckTopCollision(float t, Math::Vector::Vector4 bDegree);
	bool CheckLeftCollision(float t, Math::Vector::Vector4 bDegree);
	bool CheckRightCollision(float t, Math::Vector::Vector4 bDegree);

	//âüÇµèoÇµ
	float BottomExtrusion(ICollider* a, ICollider* b);
	float TopExtrusion(ICollider* a, ICollider* b);
	float RightExtrusion(ICollider* a, ICollider* b);
	float LeftExtrusion(ICollider* a, ICollider* b);

	void CheckExtrusion(ICollider* a, ICollider* b);
	list<ICollider*>colliders_;


};

