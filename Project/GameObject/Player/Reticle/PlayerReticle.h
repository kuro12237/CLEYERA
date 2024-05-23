#pragma once
#include"CameraData.h"
#include"Game3dObject.h"
#include"Sprite/Sprite.h"
#include"Input.h"

class PlayerReticle
{
public:
	PlayerReticle() {};
	~PlayerReticle() {};
	
	void Initialize();

	void Update();

	void Draw3d();

	void Draw2d(const CameraData& camera);

	void WorldTransformUpdate() { worldTransform_.UpdateMatrix(); }

#pragma region Set

	void SetParent(const WorldTransform& w) { worldTransform_.parent = &w; }
#pragma endregion

#pragma region Get

	Math::Vector::Vector3 GetPos() { return worldTransform_.GetWorldPosition(); }

	WorldTransform GetWorldTransform() { return worldTransform_; }

#pragma endregion


private:

	unique_ptr<Game3dObject>gameObject_ = nullptr;
	Game3dObjectDesc gameObjectDesc_ = {};

	WorldTransform worldTransform_ = {};

	Math::Vector::Vector2 joyPosition_{};

	Math::Vector::Vector3 vecPos_ = {};

};