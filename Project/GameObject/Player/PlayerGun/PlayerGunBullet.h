#pragma once
#include"Game3dObject.h"

class PlayerGunBullet
{
public:
	PlayerGunBullet() {};
	~PlayerGunBullet() {};

	void Initalize(const Math::Vector::Vector3 &spownPos,const Math::Vector::Vector3& velocity);

	void Update();

	void Draw();

#pragma region Get

	bool GetIsDeadFlag() { return isDeadFlag_; }

#pragma endregion


private:

	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform worldTransform_ = {};
	Game3dObjectDesc gameObjectDesc_ = {};

	uint32_t modelHandle_ = 0;

	Math::Vector::Vector3 velocity_ = {};

	bool isDeadFlag_ = false;

	float bulletflame_ = 0.0f;
	const float bulletflameMax_ = 120.0f;
};