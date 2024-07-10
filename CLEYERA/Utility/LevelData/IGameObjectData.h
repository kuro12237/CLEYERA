#pragma once
#include"WorldTransform.h"

class IGameObjectData
{
public:
	IGameObjectData() {};
	virtual ~IGameObjectData() {};

	void PushBackChildren(string name) { childName_.push_back(name); }

	void ImGuiUpdate(string name);

#pragma region Get

	vector<string> GetChildsName() { return childName_; }
	WorldTransform& GetWorldTransform() { return worldTransform_; }
	string GetObjectType() { return ObjectType_; }
	string GetModelFilePath() { return modelFilePath_; }

#pragma endregion

#pragma region Set

	void SetChildName(vector<string>name) { childName_ = name; }
	void SetWorldTrasform(WorldTransform wt) { worldTransform_ = wt; }
	void SetObjectType(string type) { ObjectType_ = type; }
	void SetParent(const WorldTransform& wt) { worldTransform_.SetParent(wt); }
	void SetModelFilePath(string filePath) { modelFilePath_ = filePath; }
#pragma endregion

protected:

	string ObjectType_ = "";
	WorldTransform worldTransform_;
	vector<string>childName_;
	string modelFilePath_ = "";
private:

};