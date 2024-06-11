#pragma once
#include"CameraData.h"
#include"WorldTransform.h"
#include"Game3dObject.h"
#include"Utility/CollisionManager/Collider/OBBCollider.h"
#include"Transform/STransformEular.h"
#include"Utility/LevelData/LevelData.h"

class IObjectData
{
public:
	IObjectData() {};
	virtual ~IObjectData() {};

	void Create();

	void MoveData(Game3dObjectData &data);

#pragma region Set

	void SetName(const string& name) { name_ = name; }

#pragma endregion

#pragma region Get

	string GetName() { return name_; }

	Game3dObjectDesc GetDesc() { desc_; }

#pragma endregion

private:

protected:

	string name_ = "";

	Game3dObjectDesc desc_;
	unique_ptr<Game3dObject>gameObject_ = nullptr;

	WorldTransform worldTransform_;
};