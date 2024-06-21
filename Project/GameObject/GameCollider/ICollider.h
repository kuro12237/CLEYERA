#pragma once
#include"GameObject/ObjectManager/IObjectData.h"
#include"Utility/CollisionManager/CollisionStructures/CollisionStructures.h"

enum HItDirection {
	NONE,
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
};

class ICollider
{
public:
	ICollider() {};
	virtual ~ICollider() {};

	virtual void OnCollision(ICollider* c) = 0;

#pragma region  Get

	queue<HItDirection>GetHItDirection() { return hitDirection_; }

	TransformEular GetTransform() { return *pTransform_; }

	AABB GetAABB() { return aabb; }

#pragma endregion

#pragma region Set

	void SetObjectData(const TransformEular& t) { pTransform_ = &t; }

	void SetId(uint32_t id) { id_ = id; };

#pragma endregion

private:

	queue<HItDirection>hitDirection_;
	const TransformEular* pTransform_;

	uint32_t id_ = 0b000;
	uint32_t attribute_ = 0b000;
	uint32_t mask_ = 0b000;

	AABB aabb{ {0.5f,0.5f,0.5f},{0.5f,0.5f,0.5f } };
};
