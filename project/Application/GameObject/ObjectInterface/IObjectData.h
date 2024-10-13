#pragma once
#include"WorldTransform.h"
#include"Utility/ObjectManager/GameObjectManager.h"

class GameObjectManager;
class IObjectData
{
public:
	IObjectData();
	virtual ~IObjectData() {};

	void CalcGravity(float g);

	void CreateJsonData();

#pragma region Set
	void SetName(string name) { name_ = name; }
	void SetVelocity(Math::Vector::Vector3 v) { velocity_ = v; }
#pragma endregion

#pragma region Get
	string GetName() { return name_; }
	Math::Vector::Vector3 GetVelocity() { return velocity_; }
#pragma endregion

private:

protected:

	string name_ = "";
	Math::Vector::Vector3 velocity_{};

	GlobalVariables* globalVariables_ = nullptr;
	GameObjectManager* gameObjectManager_ = nullptr;

};

