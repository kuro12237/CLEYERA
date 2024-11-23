#pragma once
#include"GameObject/ObjectInterface/ISpriteData.h"
#include"Input.h"
#include"GameObject//UI/BaseSceneBottonUI/BaseBottonUI.h"

class ClearSceneClearTextUI:public BaseBottonUI
{
public:
	ClearSceneClearTextUI() {};
	~ClearSceneClearTextUI() {};
	void Initialize(const string& groupName, const SceneUIEnum& ui)override;

private:

};
