#pragma once
#include"Game3dObject.h"
#include"Game3dInstancingObject/GameInstancing3dObject.h"
#include"PlayerGunBullet.h"

#include"Input.h"
#include"Utility/RandomGenerator/RandomGenerator.h"

#include"state/IPlayerGunState.h"
#include"state/PlayerGunAttackState.h"
#include"state/PlayerGunReloadState.h"
#include"state/PlayerGunStandState.h"

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

	void ReticlePos(const Math::Vector::Vector3& pos) { reticlePos_ = pos; }

	void SetParent(const WorldTransform& w) { worldTransform_.parent = &w; }

#pragma endregion

#pragma region Get

	Math::Vector::Vector3 GetReticlePos() { return reticlePos_; }

	WorldTransform GetworldTransform() { return worldTransform_; }

#pragma endregion

	void Attack();

	void ChangeState(PLAYERGUNSTATE state);

	bool BulletPushBack(shared_ptr<PlayerGunBullet>b);

	void BulletCountReset() { bulletCount_ = 0; }
private:


	unique_ptr<Game3dObject>gameObject_ = nullptr;
	Game3dObjectDesc gameObjectDesc_ = {};
	WorldTransform worldTransform_ = {};
	uint32_t modelHandle_ = 0;

	Math::Vector::Vector3 reticlePos_ = {};

	list<shared_ptr<PlayerGunBullet>>bullets_ = {};

	uint32_t bulletCount_ = 0;
	const uint32_t bulletCountMax_ = 10;

	unique_ptr<IPlayerGunState>state_ = {};

};