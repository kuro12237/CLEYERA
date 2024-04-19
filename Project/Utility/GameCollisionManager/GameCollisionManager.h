#pragma once
#include"GameCollider/BoxCollider.h"
#include"Pch.h"

class GameCollisonManager
{
public:
	GameCollisonManager() {};
	~GameCollisonManager() {};

	void ClearList() { colliders_.clear(); }

	void CheckAllCollisions();

	void PushList(IBoxCollider* c) { colliders_.push_back(c); }

private:

	bool CheckBottomCollsion(float t);
	bool CheckTopCollision(float t);
	bool CheckLeftCollision(float t);
	bool CheckRightCollision(float t);

	bool IsCollision(const AABB& aabb1, const AABB& aabb2);

	float BottomExtrusion(IBoxCollider* a, IBoxCollider* b);
	float TopExtrusion(IBoxCollider*a,IBoxCollider*b);
	float RightExtrusion(IBoxCollider* a, IBoxCollider* b);
	float LeftExtrusion(IBoxCollider* a, IBoxCollider* b);

	void CheckExtrusion(IBoxCollider*a,IBoxCollider*b);

	AABB SettingAABBParam(IBoxCollider* c);
	list<IBoxCollider*>colliders_ = {};
	Vector2 extrusionXY_A = {};
	Vector2 extrusionXY_B = {};


};