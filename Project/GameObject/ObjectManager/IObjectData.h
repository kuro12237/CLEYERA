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
	/// LevelData���炴�ӂ������R�s�[
	/// </summary>
	/// <param name="data"></param>
	void GetData(GameObjectManager* data);

	/// <summary>
	/// �s��X�V
	/// </summary>
	void MatUpdate();

#pragma region Set

	void SetName(string name) { name_ = name; }

#pragma endregion

#pragma region Get

	string GetName() { return name_; }

	TransformEular GetTransform() { return transform_; }

#pragma endregion


private:

protected:

	string name_ = "";

	const Math::Matrix::Matrix4x4 *worldMat_ = {};
	TransformEular transform_{};

};

