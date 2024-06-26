#pragma once
#include"WorldTransform.h"
#include"Transform/STransformEular.h"

class IGameInstancing3dObject
{
public:
	IGameInstancing3dObject() {};
	~IGameInstancing3dObject() {};

	void SetTransformEular(TransformEular t) { transform_ = t; }
	void Update();
	void SetMatWorld(const Math::Matrix::Matrix4x4& w) { mat_ = &w; }

	void SetBreakFlag(const bool& f) { breakFlag_ = f; }

#pragma region Get

	Math::Matrix::Matrix4x4 GetMatrix() { return matrix_; }

	bool GetBreakFlag() { return breakFlag_; }

	TransformEular GetTransform() { return transform_; }

#pragma endregion

private:

	const Math::Matrix::Matrix4x4* mat_ = nullptr;
	Math::Matrix::Matrix4x4 matrix_ = {};
	bool breakFlag_ = false;
	TransformEular transform_ = {};
};