#include "JoyStickUI.h"

void JoyStickUI::Initilaize(const string& joy)
{
	name_ = "GamePlay_" + joy;
	this->CreateJsonData();
	this->CreateObject();
	this->CreateJsonSpriteData();

	this->AddJsonItem("stickRad", stickRad_);
	stickRad_ = this->GetJsonItem<float>("stickRad");

	this->AddJsonItem("lerpFactor", lerpFactor_);
	lerpFactor_ = this->GetJsonItem<float>("lerpFactor");

}

void JoyStickUI::Update()
{
	this->UpdateData();
	stickRad_ = this->GetJsonItem<float>("stickRad");
	lerpFactor_ = this->GetJsonItem<float>("lerpFactor");

	Math::Vector::Vector3 reticlePos_ = {
		 stickRad_ * Input::GetJoyLStickPos().x,
		 stickRad_ * -Input::GetJoyLStickPos().y,
		 0.0f
	};

	//ï‚ä‘
	interTarget_ = Math::Vector::Lerp(interTarget_,reticlePos_, lerpFactor_);

	worldTransform_.transform.translate = Math::Vector::Add(worldTransform_.transform.translate, interTarget_);

	worldTransform_.UpdateMatrix();
}

void JoyStickUI::ImGuiUpdate()
{
}
