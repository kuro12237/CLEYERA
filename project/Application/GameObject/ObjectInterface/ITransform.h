#pragma once
#include"WorldTransform.h"

/// <summary>
/// �I�u�W�F�N�g��pos,rotate,scale�̃N���X
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