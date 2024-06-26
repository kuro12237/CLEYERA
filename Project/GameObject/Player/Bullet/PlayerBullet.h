#pragma once
#include"GameObject/ObjectManager/IObjectData.h"


class PlayerBullet:public IObjectData
{
public:
	PlayerBullet() {};
	~PlayerBullet() {};

	void Initialize();

	void Update();

#pragma region Set

	void SetSpownPos(Math::Vector::Vector3 pos) { spownPos_ = pos; }

#pragma endregion


private:

	Math::Vector::Vector3 spownPos_ = {};

};