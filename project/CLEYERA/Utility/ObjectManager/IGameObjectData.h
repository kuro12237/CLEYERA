#pragma once
#include"WorldTransform.h"
#include"Utility/GlobalVariables/GlobalVariables.h"
#include"GameObject/GameCollider/ColliderData.h"

/// <summary>
/// オブジェクトのデータ
/// </summary>
class IGameObjectData
{
public:
	IGameObjectData() {};
	virtual ~IGameObjectData() {};

	void ImGuiUpdate(string name);

	void PushBackChildren(string name) { childName_.push_back(name); }
	void PushBackParamFilePath(string name) { paramFilePaths_.push_back(name); }

	void DeleateParent() { worldTransform_.DeleateParent(); }

#pragma region Get
	vector<string> GetChildsName() { return childName_; }
	Engine::Transform::WorldTransform& GetWorldTransform() { return worldTransform_; }
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
	void SetWorldTrasform(Engine::Transform::WorldTransform wt) { worldTransform_ = wt; }
	void SetAABB(AABB aabb) { aabb_ = aabb; }
	void SetObjectType(string type) { ObjectType_ = type; }
	void SetParent(const Engine::Transform::WorldTransform& wt) { worldTransform_.SetParent(wt); }
	void SetModelFilePath(string filePath) { modelFilePath_ = filePath; }
	void SetIsDraw(const bool& f) { isDraw_ = f; }

#pragma endregion

protected:

	string ObjectType_ = "";
	std::string objectName_ = "";
	Engine::Transform::WorldTransform worldTransform_;
	//weak_ptr<Engine::Objects::Game3dObject>gameObejct_;
	AABB aabb_;
	vector<string>childName_;
	string modelFilePath_ = "";
	bool isDraw_ = true;

	vector<string>paramFilePaths_;
private:

};