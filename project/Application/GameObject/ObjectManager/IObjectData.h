#pragma once
#include"WorldTransform.h"
#include"STransformEular.h"
#include"GameObjectManager.h"

class GameObjectManager;
class IObjectData
{
public:
	IObjectData() {};
	virtual ~IObjectData() {};

	void CalcGravity(float g);

	void CreateJsonData();

#pragma region Set
	void SetName(string name) { name_ = name; }
	void SetVelocity(Math::Vector::Vector3 v) { velocity_ = v; }
	void SetUvScale(Math::Vector::Vector3 s) { uvScale_ = s; }
#pragma endregion

#pragma region Get
	string GetName() { return name_; }
	Math::Vector::Vector3 GetVelocity() { return velocity_; }
	Math::Vector::Vector3 GetUvScale() { return uvScale_; }
#pragma endregion

private:

	GlobalVariables* globalVariables_ = nullptr;

protected:

	string name_ = "";
	const Math::Matrix::Matrix4x4 *worldMat_ = {};
	Math::Vector::Vector3 velocity_{};
	Math::Vector::Vector3 uvScale_ = { 1,1,1 };

};

