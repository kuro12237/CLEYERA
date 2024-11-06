#include "JoyStickBackUI.h"

void JoyStickBackUI::Initilaize(const string& groupName, const JoyStickLeftRight& direction)
{
	name_ = groupName+"Back_" + CheckJoyStickUILeftRight(direction);

	this->CreateJsonData();
	this->CreateObject();
	this->CreateJsonSpriteData();
}

void JoyStickBackUI::Update()
{
	this->UpdateData();
	worldTransform_.UpdateMatrix();
}

void JoyStickBackUI::ImGuiUpdate()
{
}
