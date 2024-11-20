#pragma once
#include"GameObject/ObjectInterface/ISpriteData.h"
#include"Input.h"
#include"GameObject//UI/BaseSceneBottonUI/BaseBottonUI.h"


class ClearSceneCoinUI:public BaseBottonUI
{
public:
	ClearSceneCoinUI() {};
	~ClearSceneCoinUI() {};

	void Initilaize(const string& groupName, const SceneUIEnum& ui, std::function<void(BaseBottonUI& ui)>f = nullptr)override;

	void Update(BaseBottonUI& ui) { ui; };

	void SetIsActive(const bool& f) { isActive_ = f; }

private:

	bool isActive_ = false;

};
