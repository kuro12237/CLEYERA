#pragma once
#include"GameObject/ObjectInterface/ISpriteData.h"
#include"Input.h"
#include"GameObject//UI/BaseSceneBottonUI/BaseBottonUI.h"


/// <summary>
/// ジョイスティック2d表示クラス
/// </summary>
class ClearSceneJoyStick
{
public:
	ClearSceneJoyStick() {};
	~ClearSceneJoyStick() {};

	void Initialize(BaseBottonUI& ui);
	void Update(BaseBottonUI& ui);

#pragma region Get

	bool GetIsAction() { return isActionFlag_; }

#pragma endregion


private:


	bool IsLJoystickActive();

	SceneUIEnum direction_;

	float flame_ = 0.0f;

	bool isActionFlag_ = false;

};

