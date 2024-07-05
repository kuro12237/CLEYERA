#pragma once
#include"Game3dObject.h"
#include"WorldTransform.h"

#include"Game3dInstancingObject/GameInstancing3dObject.h"
#include"Transform/STransformEular.h"

class  Game3dObjectData
{
public:


	void PushBackChildren(string name) { childName_.push_back(name); }

	void Initialize(TransformEular transform, Game3dObjectDesc desc, uint32_t modelHandle);

	void WtUpdate(TransformEular transform);

#pragma region Set


	void SetData(Game3dObjectData* data);

	void SetObjName(string name) { objectName_ = name; }

	void SetModelName(string name) { modelFileName_ = name; }

	void SetGameObject(unique_ptr<Game3dObject> data) { gameObject_ = move(data); }

	void SetGameObjeDesc(Game3dObjectDesc desc) { gameObject_->SetDesc( desc); }

	void SetChildName(vector<string>name) { childName_ = name; }

	void SetMOdelHandle(uint32_t handle) { modelHandle_ = handle; }

	void SetWorldTrasform(WorldTransform wt) { worldTransform_ = wt; }

	void SetParent(const WorldTransform& wt) { worldTransform_.SetParent(wt); }

#pragma endregion

#pragma region Get

	vector<string> GetChildsName() { return childName_; }

	string GetObjectName() { return objectName_; }

	WorldTransform& GetWorldTransform() { return worldTransform_; }

	unique_ptr<Game3dObject>& GetGameObject() { return gameObject_; }

	Game3dObjectDesc GetDesc() { return objectDesc_; }

#pragma endregion

private:
	std::string objectName_;
	std::string modelFileName_;
	WorldTransform worldTransform_;
	Game3dObjectDesc objectDesc_;
	unique_ptr<Game3dObject>gameObject_;
	uint32_t modelHandle_ = 0;
	vector<string>childName_;
};

