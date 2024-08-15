#pragma once
#include"GameObject/ObjectManager/IObjectData.h"

class PlayerGun:public IObjectData
{
public:
	PlayerGun() {};
	~PlayerGun() {};

	void Initialize();

	void Update();

#pragma region Set

	void SetTarget(Math::Vector::Vector3 t) { targetPos_ = t; }

#pragma endregion


private:

	Math::Vector::Vector3 targetPos_ = {};

};