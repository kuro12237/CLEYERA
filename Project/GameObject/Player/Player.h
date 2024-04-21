#pragma once
#include"Game3dObject.h"
#include"Input.h"
#include"Utility/GameCollisionManager/GameCollider/BoxCollider.h"
#include"Utility/GameGravityManager/IGravity.h"
#include"Utility/GameCollisionManager/GameColliderConfig.h"
#include"Utility/GlobalVariables/GlobalVariables.h"
#include"Utility/ObjectId/GameObjectId.h"
#include"Audio/AudioManager.h"
#include"Utility/CollisionManager/Collider/OBBCollider.h"

class Player:public IBoxCollider,public IGravity,public OBBCollider
{
public:
	Player() {};
	~Player() {};

	void Initialize();

	void Update();

	void Draw(const CameraData& camera);

	void ImGuiUpdate();

	void OnBlockCollision(IBoxCollider* collider)override;
	void OnCollision(uint32_t id)override;

	void GravityExc(const Math::Vector::Vector2 &g)override;

#pragma region Command

	void Move();

	void Jamp();

#pragma endregion

#pragma region Get

	const WorldTransform& GetWorldTransform() { return worldTransform_; }
	Math::Vector::Vector3 GetWorldPosition()override;
	Math::Vector::Vector3 GetSize()override;
	Math::Vector::Vector3 GetRotate()override;

#pragma endregion

#pragma region Set

	void SetParent(const WorldTransform& w) { worldTransform_.parent = &w; }

#pragma endregion

private:

	uint32_t modelHandle_ = 0;
	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform worldTransform_{};

	AABB aabb_ = {};
	Math::Vector::Vector2 velocity_ = {};

	bool isJamp_ = false;

	Math::Vector::Vector3 GameStartPos_ = {};

	Game3dObjectDesc game3dObjectdesc_ = {};
};

