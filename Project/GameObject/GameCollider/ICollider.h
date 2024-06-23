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


	void ClearExtrusion() { extrusion_={}; }

	void ClearHitDirection() { hitDirection_.clear(); }

	void PushBackHitDirection(HItDirection h) { hitDirection_.push_back(h); }
    
#pragma region  Get

	vector<HItDirection>GetHItDirection() { return hitDirection_; }

	TransformEular GetpTransform() { return *pTransform_; }

	AABB GetAABB() { return aabb; }

	bool GetIsExtrusionFlag() { return isExtrusion_; }

#pragma endregion

#pragma region Set

	void SetObjectData(const TransformEular& t) { pTransform_ = &t; }

	void SetId(uint32_t id) { id_ = id; };

	void SetExtrusion(Math::Vector::Vector2 v) { extrusion_ = v; }

#pragma endregion

protected:

	bool isExtrusion_ = false;
	Math::Vector::Vector2 extrusion_ = {};
	vector<HItDirection>hitDirection_;

private:

	const TransformEular* pTransform_;

	uint32_t id_ = 0b000;
	uint32_t attribute_ = 0b000;
	uint32_t mask_ = 0b000;

	AABB aabb{{ -1.0f,-1.0f,-1.0f }, { 1.0f,1.0f,1.0f }};


};
