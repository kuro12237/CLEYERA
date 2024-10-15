#pragma once
#include"WorldTransform.h"
#include"Utility/CollisionManager/CollisionStructures/CollisionStructures.h"
#include"Utility/GlobalVariables/GlobalVariables.h"

class IGameObjectData
{
public:
	IGameObjectData() {};
	virtual ~IGameObjectData() {};

	void ImGuiUpdate(string name);

	void PushBackChildren(string name) { childName_.push_back(name); }
	void PushBackParamFilePath(string name) { paramFilePaths_.push_back(name); }

#pragma region Get
	vector<string> GetChildsName() { return childName_; }
	WorldTransform& GetWorldTransform() { return worldTransform_; }
	string GetObjectType() { return ObjectType_; }
	string GetObjectName() { return objectName_; }
	bool GetIsDraw() { return isDraw_; }
	AABB GetAABB() { return aabb_; }
	string GetModelFilePath() { return modelFilePath_; }
	vector<string>& GetParamFilePaths() { return paramFilePaths_; }
#pragma endregion

#pragma region Set
	void SetObjName(string name) { objectName_ = name; }
	void SetChildName(vector<string>name) { childName_ = name; }
	void SetWorldTrasform(WorldTransform wt) { worldTransform_ = wt; }
	void SetAABB(AABB aabb) { aabb_ = aabb; }
	void SetObjectType(string type) { ObjectType_ = type; }
	void SetParent(const WorldTransform& wt) { worldTransform_.SetParent(wt); }
	void SetModelFilePath(string filePath) { modelFilePath_ = filePath; }
#pragma endregion

protected:

	string ObjectType_ = "";
	std::string objectName_ = "";
	WorldTransform worldTransform_;
	AABB aabb_;
	vector<string>childName_;
	string modelFilePath_ = "";
	bool isDraw_ = true;

	vector<string>paramFilePaths_;

private:

};