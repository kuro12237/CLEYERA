#pragma once
#include"Game3dObject.h"
#include"Animation/AnimationManager.h"
#include"OBBCollider.h"
#include"AudioManager.h"

class Item : public OBBCollider
{
public:
	Item() {};
	~Item() {};

	void Initialize();

	void Update();

	void Animation();

	void Draw(const CameraData& camera);

	void OnCollision(uint32_t id)override;

#pragma region Set

#pragma endregion

#pragma region Get

	Math::Vector::Vector3 GetWorldPosition()override;
	Math::Vector::Vector3 GetSize()override;
	Math::Vector::Vector3 GetRotate()override;

	bool GetIsDeadFlag() { return isDeadFlag_; }

#pragma endregion

private:

	unique_ptr<Game3dObject>gameObject_ = nullptr;
	Game3dObjectDesc gameObjectDesc_ = {};

	WorldTransform worldTransform_ = {};

	uint32_t animationHandle_ = 0;
	float animationTimer_ = 0.0f;

	bool isDeadFlag_ = false;
};
