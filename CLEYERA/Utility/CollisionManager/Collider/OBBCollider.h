#pragma once
#include "Pch.h"
#include "CollisionStructures/CollisionStructures.h"


class OBBCollider {

public:

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	virtual void OnCollision(uint32_t id) = 0;

	/// <summary>
	/// ワールド座標の取得
	/// </summary>
	virtual Math::Vector::Vector3 GetWorldPosition() = 0;

#pragma region Size

	/// <summary>
	/// Sizeの取得
	/// </summary>
	virtual Math::Vector::Vector3 GetSize() = 0;

	/// <summary>
	/// Sizeの設定
	/// </summary>
	void SetSize(Math::Vector::Vector3 size) { size_ = size; }

#pragma endregion

#pragma region Rotate

	/// <summary>
	/// Rotateの取得
	/// </summary>
	virtual Math::Vector::Vector3 GetRotate() = 0;

	/// <summary>
	/// Rotateの設定
	/// </summary>
	void SetRotate(Math::Vector::Vector3 rotate) { rotate_ = rotate; }

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

	OBB obb_{};

	uint32_t id_ = 0xffffffff;

	uint32_t collisionAttribute_ = 0xffffffff;

	uint32_t CollisionMask_ = 0xffffffff;

	Math::Vector::Vector3 size_ = { 1.0f, 1.0f ,1.0f };

	Math::Vector::Vector3 rotate_ = { 0.0f, 0.0f, 0.0f };
};