#pragma once
#include"STransformEular.h"
#include"Pch.h"
#include"GameObject/ObjectInterface/IObjectData.h"

#include"GameObject/GameCollider/ICollider.h"
#include"Input.h"
#include"Utility/ObjectId/GameObjectId.h"

/// <summary>
/// �N���A�V�[���ł̃L�����N�^�[�̍X�V
/// </summary>
class ClearCharacter :public IObjectData
{
public:
	ClearCharacter() {};
	~ClearCharacter() {};

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

private:

	SAnimation::Animation animationData_ = {};

	float animFlame_ = 0.0f;

};
