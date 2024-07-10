#pragma once
#include"Game3dObject.h"
#include"WorldTransform.h"

#include"Game3dInstancingObject/GameInstancing3dObject.h"
#include"Transform/STransformEular.h"
#include"IGameObjectData.h"

class  Game3dObjectData:public IGameObjectData
{
public:

	void Initialize(TransformEular transform, Game3dObjectDesc desc, uint32_t modelHandle);

	void WtUpdate(TransformEular transform);

#pragma region Set

	void SetData(Game3dObjectData* data);

	void SetObjName(string name) { objectName_ = name; }

	void SetModelName(string name) { modelFileName_ = name; }

	void SetGameObject(unique_ptr<Game3dObject> data) { gameObject_ = move(data); }

	void SetGameObjeDesc(Game3dObjectDesc desc) { gameObject_->SetDesc( desc); }

	void SetMOdelHandle(uint32_t handle) { modelHandle_ = handle; }

	void SetAABB(AABB aabb) { aabb_ = aabb; }

#pragma endregion

#pragma region Get

	string GetObjectName() { return objectName_; }

	unique_ptr<Game3dObject>& GetGameObject() { return gameObject_; }

	Game3dObjectDesc GetDesc() { return objectDesc_; }

	AABB GetAABB() { return aabb_; }
#pragma endregion

private:
	std::string objectName_;
	std::string modelFileName_;
	Game3dObjectDesc objectDesc_;
	unique_ptr<Game3dObject>gameObject_;
	uint32_t modelHandle_ = 0;
	AABB aabb_;

	SAnimation::Skeleton skelton_ = {};
	SAnimation::Animation animationData_;

	float animationFlame_ = 0.0f;
};

