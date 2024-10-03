#pragma once
#include"WorldTransform.h"
#include"Transform/STransformEular.h"
#include"Utility/CollisionManager/CollisionStructures/CollisionStructures.h"

class IGameInstancing3dObject
{
public:
	IGameInstancing3dObject() {};
	~IGameInstancing3dObject() {};

	void SetTransformEular(TransformEular t) { transform_ = t; }
	void Update();

	void SetBreakFlag(const bool& f) { breakFlag_ = f; }

	void SetAABB(AABB aabb) { aabb_ = aabb; }

	void SetUvScale(Math::Vector::Vector3 s) { uvScale_ = s; }
	void SetParent(const Math::Matrix::Matrix4x4& parent) { parent_ = &parent; }

#pragma region Get

	Math::Matrix::Matrix4x4 GetMatrix() { return matrix_; }

	bool GetBreakFlag() { return breakFlag_; }

	TransformEular &GetTransform() { return transform_; }

	AABB GetAABB() { return aabb_; }

	Math::Vector::Vector3 GetUvScale() { return uvScale_; }

	vector<string>&GetParentNames() { return parentNames_; }
	string &GetName() { return name_; }

#pragma endregion

private:

	Math::Matrix::Matrix4x4 matrix_ = {};
	bool breakFlag_ = false;
	TransformEular transform_ = {};
	AABB aabb_ = {};
	Math::Vector::Vector3 uvScale_ = { 1,1,1 };
	string name_ = "";
	vector<string> parentNames_;

	const Math::Matrix::Matrix4x4* parent_ = nullptr;
};