#pragma once
#include"WorldTransform.h"

/// <summary>
/// オブジェクトのpos,rotate,scaleのクラス
/// </summary>
class ITransform
{
public:
	ITransform() = default;
	virtual ~ITransform() = default;

#pragma region Get
	Engine::Transform::WorldTransform GetWorldTransform() const { return worldTransform_; }
#pragma endregion

private:

protected:

	Engine::Transform::WorldTransform worldTransform_ = {};

};