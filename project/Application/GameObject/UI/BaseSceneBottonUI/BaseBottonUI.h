#pragma once
#include"GameObject/ObjectInterface/ISpriteData.h"
#include"Input.h"
#include"../GameSceneUI/GameSceneUIData.h"


class BaseBottonUI :public ISpriteData
{
public:
	BaseBottonUI() {};
	~BaseBottonUI() {};

	/// <summary>
	/// èâä˙âª
	/// </summary>
	void Initilaize(const string& groupName, const SceneUIEnum& ui,std::function<void(BaseBottonUI& ui)>f = nullptr);

	/// <summary>
	/// çXêV
	/// </summary>
	void Update();

	void ImGuiUpdate()override;


#pragma region Set
	void SetControlActionFunction(std::function<bool()>f) { controlFunc_ = f; };
	void SetIsActionActiveFunction(std::function<void(BaseBottonUI& ui)>f) { isActionTrueFunc_ = f; };
	void SetIsActionInactiveFunction(std::function<void(BaseBottonUI& ui)>f) { isActionFalseFunc_ = f; };

	void SetUpdateFunction(std::function<void(BaseBottonUI& ui)>f) { updateFunc_ = f; };
#pragma endregion

#pragma region Get
	SceneUIEnum GetUIEnum(){ return ui_; }
#pragma endregion


private:
	std::function<bool()> controlFunc_;
	std::function<void(BaseBottonUI& ui)>isActionTrueFunc_;
	std::function<void(BaseBottonUI& ui)>isActionFalseFunc_;
	std::function<void(BaseBottonUI& ui)> updateFunc_;
	std::function<void(BaseBottonUI& ui)> initializeFunc_;

	bool isAction_ = false;

	SceneUIEnum ui_ = SceneUIEnum::JoyStick_None;
};