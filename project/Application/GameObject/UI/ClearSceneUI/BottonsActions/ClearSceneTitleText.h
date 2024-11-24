#pragma once
#include"GameObject/ObjectInterface/ISpriteData.h"
#include"Input.h"
#include"GameObject//UI/BaseSceneBottonUI/BaseBottonUI.h"

/// <summary>
/// ジョイスティック2d表示クラス
/// </summary>
class ClearSceneTitleText :public BaseBottonUI
{
public:
	ClearSceneTitleText() {};
	~ClearSceneTitleText() {};


	void Initialize(const string& groupName, const SceneUIEnum& ui)override;


#pragma region Get

#pragma endregion

	void SetisSelect(bool f) { isSelect_ = f; }

private:

	void UiUpdate();


	bool isSelect_ = false;
	float flame_ = 0.0f;
	float flameMax_ = 1.0f;
};

