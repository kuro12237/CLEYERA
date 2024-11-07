#pragma once
#include"GameObject/ObjectInterface/ISpriteData.h"
#include"Input.h"
#include"../GameSceneUIData.h"
#include"GameObject//UI/BaseSceneBottonUI/BaseBottonUI.h"

/// <summary>
/// �W���C�X�e�B�b�N2d�\���N���X
/// </summary>
class GameSceneJoyStick
{
public:
	GameSceneJoyStick() {};
	~GameSceneJoyStick() {};

	void Active(BaseBottonUI& ui);

	void Inactive(BaseBottonUI& ui);

	void Initialize(BaseBottonUI& ui);
	void Update(BaseBottonUI& ui);

private:

	SceneUIEnum direction_;

	float stickRad_ = 0.0f;
	float lerpFactor_ = 0.0f;

	Math::Vector::Vector3 interTarget_ = {};

};

