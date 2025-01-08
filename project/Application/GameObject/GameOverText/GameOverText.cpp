#include "GameOverText.h"

void GameOverText::Initialize()
{
	name_ = "GameOverText";
	this->CreateJsonData("GameOverScene/");
	this->CreateObject();
	this->CreateJsonSpriteData();
	this->CalcAnkerPos();

}

void GameOverText::ImGuiUpdate()
{
	string label = name_ + "LoadData";
	if (ImGui::Button(label.c_str()))
	{
		this->UpdateData();
	}

}
void GameOverText::Update()
{


	this->CalcAnkerPos();
	if (flame_<=flameMax_)
	{
		flame_ += 1.0f/120.0f;
	}

	
	float scaleSpeed = Math::Vector::LerpEaseOutSine(0.0f, scaleMax_, flame_);
	worldTransform_.transform.scale = { scaleSpeed,scaleSpeed,scaleSpeed };

	worldTransform_.UpdateMatrix();

}
