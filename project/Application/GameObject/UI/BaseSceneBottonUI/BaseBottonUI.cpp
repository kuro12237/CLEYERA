#include "BaseBottonUI.h"

void BaseBottonUI::Initialize(const string& groupName, const SceneUIEnum& ui)
{
	CreateUIData(groupName,ui);

	//初期化関数代入呼び出し
	
}

void BaseBottonUI::Update()
{
	this->UpdateData();

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

	
	//更新
	if (updateFunc_)
	{
		updateFunc_(*this);
	}

	worldTransform_.UpdateMatrix();
	this->UpdateTextureData();
}

void BaseBottonUI::ImGuiUpdate()
{
}

void BaseBottonUI::CreateUIData(const string& groupName, const SceneUIEnum& ui)
{
	name_ = groupName + CheckSceneUIEnumtoString(ui);
	ui_ = ui;

	this->CreateJsonData();
	this->CreateObject();
	this->CreateJsonSpriteData();

}
