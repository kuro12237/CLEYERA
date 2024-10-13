#pragma once
#include"Game3dObject.h"
#include"WorldTransform.h"

#include"Game3dInstancingObject/GameInstancing3dObject.h"
#include"Transform/STransformEular.h"

class Game3dInstancingObjectData
{
public:

	void Initialize(string objectType, uint32_t modelHandle);
	
	void ImGuiUpdate();

	void PushBackTransform(shared_ptr<IGameInstancing3dObject>t) { transform_.push_back(t); }
	void PushObjectData(shared_ptr<IGameInstancing3dObject>t, uint32_t size) { gameInstancingObject_->PushVector(t, size); }
	void PushObjectData(uint32_t size);

	void TransfarData() { gameInstancingObject_->Transfar(); }

	void SetParent(string childName, string parentName) { childName, parentName; }

#pragma region Get

	vector<shared_ptr<IGameInstancing3dObject>>&GetTransforms() { return transform_; }
	unique_ptr<GameInstancing3dObject>&GetGameObject() { return gameInstancingObject_; }
	string GetObjectType() { return objectType_; }
#pragma endregion
private:
	string objectType_;
	std::string modelFileName_;
	unique_ptr<GameInstancing3dObject>gameInstancingObject_ = nullptr;
	vector<shared_ptr<IGameInstancing3dObject>>transform_;
	uint32_t modelHandle_ = 0;
	const uint32_t instanceMax_ = 512;

};