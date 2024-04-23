#pragma once
#include"WorldTransform.h"

class IGameInstancing3dObject
{
public:
	IGameInstancing3dObject() {};
	virtual ~IGameInstancing3dObject() {};

	void SetMatWorld(const Math::Matrix::Matrix4x4& w) { mat_ = &w; }

	void SetBreakFlag(const bool& f) { breakFlag_ = f; }

	Math::Matrix::Matrix4x4 GetMatrix() { return *mat_; }

	bool GetBreakFlag() { return breakFlag_; }
private:

	const Math::Matrix::Matrix4x4* mat_ = nullptr;
	bool breakFlag_ = false;

};