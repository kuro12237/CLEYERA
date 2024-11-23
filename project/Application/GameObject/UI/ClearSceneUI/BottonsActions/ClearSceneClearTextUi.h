#pragma once
#include"GameObject/ObjectInterface/ISpriteData.h"
#include"Input.h"
#include"GameObject//UI/BaseSceneBottonUI/BaseBottonUI.h"

/// <summary>
/// クリア表示
/// </summary>
class ClearSceneClearTextUI:public BaseBottonUI
{
public:
	ClearSceneClearTextUI() {};
	~ClearSceneClearTextUI() {};

	void Initialize(const string& groupName, const SceneUIEnum& ui)override;

#pragma region Set

	void SetIsStart(bool f) { isStart_ = f; }

#pragma endregion


private:

	void UiUpdate();

	bool isStart_ = false;

	float flame_ = 0.0f;
	float flameMax_ = 1.0f;
};
