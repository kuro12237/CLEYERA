#pragma once
#include"Lava.h"
#include"GameObject/ObjectManager/GameObjectManager.h"

class Lava :public IObjectData
{
public:
	Lava() {};
	~Lava() {};

	void Initialize();

	void Update();

#pragma region Set

	void SetCameraParent(const Math::Vector::Vector3 &pos) { p_CameraPos_ = &pos; }

#pragma endregion


private:

	GameObjectManager* gameObjectManager_ = nullptr;
	const Math::Vector::Vector3* p_CameraPos_ = nullptr;

};