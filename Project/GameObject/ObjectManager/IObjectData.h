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

	/// <summary>
	/// objectManager����f�[�^���R�s�[
	/// </summary>
	/// <param name="data"></param>
	void GetData(GameObjectManager* data);

	void CalcGravity(float g);

#pragma region Set

	void SetName(string name) { name_ = name; }

	void SetTransform(TransformEular t) { transform_ = t; }

	void SetVelocity(Math::Vector::Vector3 v) { velocity_ = v; }

#pragma endregion

#pragma region Get

	string GetName() { return name_; }

	TransformEular GetTransform() { return transform_; }

	Math::Vector::Vector3 GetVelocity() { return velocity_; }

#pragma endregion

private:

protected:

	string name_ = "";

	const Math::Matrix::Matrix4x4 *worldMat_ = {};
	TransformEular transform_{};
	Math::Vector::Vector3 velocity_{};
};
