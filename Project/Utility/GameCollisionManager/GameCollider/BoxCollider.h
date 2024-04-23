#pragma once
#include"CollisionStructures/CollisionStructures.h"

#include"Pch.h"
#include"WorldTransform.h"

class IBoxCollider
{
public:
	IBoxCollider() {};
	~IBoxCollider() {};

	virtual void OnBlockCollision(IBoxCollider*collider) = 0;
	virtual Math::Vector::Vector3 GetWorldPosition() = 0;

	void ClearFlag() { bottomHitFlag_ = false; topHitFlag_ = false; rightHitFlag_ = false; leftHitFlag_ = false; };

#pragma region Set

	void SetAABB(const AABB& aabb) { aabb_ = &aabb; }

	void SetAttbute(const uint32_t& a) { attbute_ = a;}
	void SetMask(const uint32_t& m) { mask_ = m; }

	void HitBottom(bool f) { bottomHitFlag_ = f; };
	void HitTop(bool f) { topHitFlag_ = f; }
	void HitLeft(bool f) { leftHitFlag_ = f; }
	void HitRight(bool f) { rightHitFlag_ = f; }

	void SetExtrusion(const Math::Vector::Vector2& e) { extrusion_ = e; }

	void SetVelocity(const Math::Vector::Vector2& v) { velocity_ = &v; }

	void SetId(const uint32_t& id) { id_ = id; }

	void SetWorldTransform(const WorldTransform& w) { worldTransform_ = &w; }

#pragma endregion 

#pragma region get
	Math::Vector::Vector2 GetVelocity() { return *velocity_; }

	bool GetBottomFlag() { return bottomHitFlag_; }
	bool GetTopFlag() { return topHitFlag_; }
	bool GetLeftFlag() { return leftHitFlag_; }
	bool GetRightFlag() { return rightHitFlag_; }

	AABB GetAABB() { return *aabb_; }
	Math::Vector::Vector2 GetExtrusionXY() { return extrusion_; }

	uint32_t GetAttbute() { return attbute_; }
	uint32_t GetMask() { return mask_; }

	uint32_t GetId() { return id_; }

	WorldTransform GetWorldTransform() { return *worldTransform_; }
#pragma endregion

private:

	bool bottomHitFlag_ = false;
	bool topHitFlag_ = false;
	bool leftHitFlag_ = false;
	bool rightHitFlag_ = false;

	const AABB* aabb_ = {};
	Math::Vector::Vector2 extrusion_ = {};

	uint32_t id_ = 0b0000001;
	const Math::Vector::Vector2* velocity_ = {};

	uint32_t attbute_ = 0b00000001;
	uint32_t mask_ = 0b00000001;
	const WorldTransform* worldTransform_;
};