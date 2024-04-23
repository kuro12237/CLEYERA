#pragma once
#include"Game3dObject.h"
#include"Game3dInstancingObject/GameInstancing3dObject.h"
#include"PlayerGunBullet.h"

#include"Input.h"

class PlayerGun
{
public:
	PlayerGun() {};
	~PlayerGun() {};

	void Initlalize();

	void Update();

	void Animation();

	void Draw(const CameraData& camera);

	void WorldTransformUpdate() { worldTransform_.UpdateMatrix(); }

	void ImGuiUpdate();

#pragma region Set

	void ReticlePos(const Math::Vector::Vector3& pos) { reticlePos = pos; }

	void SetParent(const WorldTransform& w) { worldTransform_.parent = &w; }

#pragma endregion

	void Attack();

private:

	unique_ptr<Game3dObject>gameObject_ = nullptr;
	Game3dObjectDesc gameObjectDesc_ = {};
	WorldTransform worldTransform_ = {};
	uint32_t modelHandle_ = 0;

	Math::Vector::Vector3 reticlePos = {};

	list<shared_ptr<PlayerGunBullet>>bullets_ = {};

};