#include "BaseBottonUI.h"

void BaseBottonUI::Initilaize(const string& groupName, const SceneUIEnum& ui)
{
	name_ = groupName + CheckSceneUIEnumtoString(ui);

	this->CreateJsonData();
	this->CreateObject();
	this->CreateJsonSpriteData();
}

void BaseBottonUI::Update()
{
	//コントロール関数呼び出し
	if (controlFunc_)
	{
		if (controlFunc_())
		{
			isAction_ = true;
		}
		else
		{
			isAction_ = false;
		}
	}

	//コントロールされているとき
	if (isAction_)
	{
		if (isActionTrueFunc_)
		{
			isActionTrueFunc_(*this);
		}
	}
	else
	{
		if (isActionFalseFunc_)
		{
			isActionFalseFunc_(*this);
		}
	}

	this->UpdateData();

	worldTransform_.UpdateMatrix();
}

void BaseBottonUI::ImGuiUpdate()
{
}
