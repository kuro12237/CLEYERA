#pragma once
#include"GameObject/ObjectManager/GameObjectManager.h"
#include"state/IArchState.h"

class Arch :public IObjectData
{
public:
	Arch() {};
	~Arch() {};

	void Initialize();

	void Update();
#pragma region Set

	void SetStart(bool flag) { isStart_ = flag; }
	void SetCameraPos(const Math::Vector::Vector3& pos) { p_CameraPos_ = &pos; }
#pragma endregion


private:

	GameObjectManager* gameObjectManager_ = nullptr;
	bool isStart_ = false;
	const Math::Vector::Vector3* p_CameraPos_ = nullptr;
};
