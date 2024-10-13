#pragma once

#include"Utility/ObjectManager/GameObjectManager.h"
#include"GameObject/ObjectInterface/IObjectData.h"

class PlayerCamera:public IObjectData
{
public:
	PlayerCamera() {};
	~PlayerCamera() {};

	void Initialize();

	void Update();

#pragma region Set

	void SetTargetName(string target) { targetName_ = target; }

#pragma endregion

#pragma region Get

#pragma endregion

private:

	Math::Vector::Vector3 CalcOffset(const WorldTransform& w ,const Math::Vector::Vector3 v)const;

	GameObjectManager* gameObjInstance_ = nullptr;
	string targetName_ = "";
	const WorldTransform* target_ = nullptr;

	Math::Vector::Vector3 interTarget_{};
	float distructionAngleY_ = 0.0f;
	float lerp_t = 0.0f;
};

