#include "ClearSceneCoinUI.h"

void ClearSceneCoinUI::Initilaize(const string& groupName, const SceneUIEnum& ui, std::function<void(BaseBottonUI& ui)> f)
{
	this->CreateUIData(groupName, ui);

	string activeName = "";
	this->AddJsonItem("activeTex", activeName);
	activeName = this->GetJsonItem<string>("activeTex");

	string inActiveName = "";
	this->AddJsonItem("inActiveTex", inActiveName);
	inActiveName = this->GetJsonItem<string>("inActiveTex");

	if (isActive_)
	{
		this->fileName_ = activeName;
	}
	else
	{
		this->fileName_ = inActiveName;
	}


}
