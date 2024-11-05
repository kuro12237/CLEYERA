#include "JoyStickBackUI.h"

void JoyStickBackUI::Initilaize(const string& joy)
{
	name_ = "GameJoyStick_Back_" + joy;
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
