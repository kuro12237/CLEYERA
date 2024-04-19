#pragma once
#include"Game3dInstancingObject/IGameInstancing3dObject.h"
#include"Utility/GameCollisionManager/GameCollider/BoxCollider.h"
#include"Utility/GameCollisionManager/GameColliderConfig.h"
#include"Utility/ObjectId/GameObjectId.h"

class WoodBlock : public IGameInstancing3dObject,public IBoxCollider
{
public:
	WoodBlock() {};
	~WoodBlock() {};

	void Initialize(const TransformQua &t);

	void Update();

	Math::Vector::Vector3 GetWorldPosition()override;

	void OnCollision(IBoxCollider* collider)override;

	void SetTransformQua(const TransformQua& q);

	void SetNumber(uint32_t n) { blockNamber_ = n; }

	uint32_t GetNumber() { return blockNamber_; }
	bool GetIsHit() { return isHit_; }

	void UpdateImGui();

private:

	Math::Matrix::Matrix4x4 worldMat_ = {};

	Math::Vector::Vector3 scale_ = {1,1,1};
	Math::Vector::Vector3 rotate_ = {};
	Math::Vector::Vector3 translate_ = {};

	AABB aabb_;

	uint32_t blockNamber_ = 0;

	bool isHit_ = false;
	Math::Vector::Vector2 velocity_ = {};
};
