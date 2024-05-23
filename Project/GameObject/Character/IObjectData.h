#pragma once
#include"CameraData.h"
#include"WorldTransform.h"
#include"Game3dObject.h"
#include"Utility/CollisionManager/Collider/OBBCollider.h"
#include"Transform/STransformEular.h"

class IObjectData
{
public:
	IObjectData() {};
	virtual ~IObjectData() {};

	void GameObjectCreate(const string filePath, const Game3dObjectDesc& desc);
	void WtCreate(const TransformEular& transform, const WorldTransform* wt);

	void UpdateMat();

	void DrawObject();

#pragma region Set

	void SetName(const string& name) { name_ = name; }

	void SetGameObkectDesc(Game3dObjectDesc desc) { desc_ = desc; }
#pragma endregion

#pragma region Get

	string GetName() { return name_; }

	Game3dObjectDesc GetDesc() { desc_; }

#pragma endregion

private:

	string name_ = "";

	Game3dObjectDesc desc_;
	unique_ptr<Game3dObject>gameObject_ = nullptr;

	WorldTransform worldTransform_;

};