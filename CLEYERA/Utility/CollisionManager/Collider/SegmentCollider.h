#pragma once
#include"Pch.h"
#include "CollisionStructures/CollisionStructures.h"


class SegmentCollider {
public:

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	virtual void OnCollision(uint32_t id) = 0;

	/// <summary>
	/// ワールド座標の取得
	/// </summary>
	virtual Math::Vector::Vector3 GetWorldPosition() = 0;

#pragma region Segment

	/// <summary>
	/// Radiusの取得
	/// </summary>
	Segment GetSegments() { return segment_; }

	/// <summary>
	/// Radiusの設定
	/// </summary>
	void SetRadius(Segment segment) { segment_ = segment; }

#pragma endregion 

#pragma region ID

	/// <summary>
	/// IDの取得
	/// </summary>
	uint32_t GetID() { return id_; }

	/// <summary>
	/// IDの設定
	/// </summary>
	void SetID(uint32_t id) { id_ = id; }

#pragma endregion 

#pragma region CollisionAttribute

	/// <summary>
	/// collisionAttributeの取得
	/// </summary>
	uint32_t GetCollosionAttribute() const { return collisionAttribute_; }

	/// <summary>
	/// collisionAttributeの設定
	/// </summary>
	void SetCollosionAttribute(uint32_t collisionAttribute) { collisionAttribute_ = collisionAttribute; }

#pragma endregion

#pragma region CollisionMask

	/// <summary>
	/// CollisionMaskの取得
	/// </summary>
	uint32_t GetCollisionMask() const { return CollisionMask_; }

	/// <summary>
	/// CollisionMaskの設定
	/// </summary>
	void SetCollisionMask(uint32_t collisionMask) { CollisionMask_ = collisionMask; }

#pragma endregion

private:

	uint32_t collisionAttribute_ = 0xffffffff;

	uint32_t CollisionMask_ = 0xffffffff;

	uint32_t id_ = 0xffffffff;

	Segment segment_{};
};
