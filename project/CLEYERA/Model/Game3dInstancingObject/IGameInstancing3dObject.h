#pragma once
#include"WorldTransform.h"
#include"Transform/STransformEular.h"
#include"GameObject/GameCollider/ColliderData.h"

class IGameInstancing3dObject
{
public:
	IGameInstancing3dObject() {};
	~IGameInstancing3dObject() {};

	/// <summary>
	/// çXêV
	/// </summary>
	void Update();

#pragma region Set
	void SetTransformEular(Engine::Transform::TransformEular t) { transform_ = t; }
	void SetBreakFlag(const bool& f) { breakFlag_ = f; }
	void SetAABB(AABB aabb) { aabb_ = aabb; }
	void SetUvScale(Math::Vector::Vector3 s) { uvScale_ = s; }
	void SetParent(const Math::Matrix::Matrix4x4& parent) { parent_ = &parent; }
#pragma endregion

#pragma region Get
	Math::Matrix::Matrix4x4 GetMatrix() { return matrix_; }
	bool GetBreakFlag() { return breakFlag_; }
	Engine::Transform::TransformEular &GetTransform() { return transform_; }
	Math::Vector::Vector4 &GetColor() { return color_; }
	AABB GetAABB() { return aabb_; }
	Math::Vector::Vector3 GetUvScale() { return uvScale_; }
	vector<string>&GetParentNames() { return parentNames_; }
	string &GetName() { return name_; }
#pragma endregion

private:

	Math::Matrix::Matrix4x4 matrix_ = {};
	bool breakFlag_ = false;
	Engine::Transform::TransformEular transform_ = {};
	AABB aabb_ = {};
	Math::Vector::Vector3 uvScale_ = { 1.0f,1.0f,1.0f };
	Math::Vector::Vector4 color_ = { 1.0f,1.0f,1.0f,1.0f };
	string name_ = "";
	vector<string> parentNames_;

	const Math::Matrix::Matrix4x4* parent_ = nullptr;
};