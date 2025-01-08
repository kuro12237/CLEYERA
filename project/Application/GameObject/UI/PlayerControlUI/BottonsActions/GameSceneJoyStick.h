#pragma once
#include"GameObject/ObjectInterface/ISpriteData.h"
#include"Input.h"
#include"../GameObject/UI/GameSceneUI/GameSceneUIData.h"
#include"GameObject//UI/BaseSceneBottonUI/BaseBottonUI.h"

/// <summary>
/// ジョイスティック2d表示クラス
/// </summary>
class GameSceneJoyStick:public BaseBottonUI
{
public:
	GameSceneJoyStick() {};
	~GameSceneJoyStick() {};

	void Active(BaseBottonUI& ui);

	void Inactive(BaseBottonUI& ui);

	void Initialize(const string& groupName, const SceneUIEnum& ui)override;
	void Update(BaseBottonUI& ui);

private:

	SceneUIEnum direction_;

	float stickRad_ = 0.0f;
	float lerpFactor_ = 0.0f;

	Math::Vector::Vector3 interTarget_ = {};
	bool IsLJoystickActive();

};

