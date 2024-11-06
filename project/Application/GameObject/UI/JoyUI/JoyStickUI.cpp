#include "JoyStickUI.h"

void JoyStickUI::Initilaize(const string& groupName, const JoyStickLeftRight& direction)
{
	direction_ = direction;
	name_ = groupName + CheckJoyStickUILeftRight(direction);

	this->CreateJsonData();
	this->CreateObject();
	this->CreateJsonSpriteData();

	//í≤êÆçÄñ⁄í«â¡
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

	Math::Vector::Vector3 reticlePos_{};

	if (direction_==JoyStickLeftRight::Left)
	{
		reticlePos_.x = Input::GetJoyLStickPos().x;
		reticlePos_.y = Input::GetJoyLStickPos().y;
	}
	if (direction_ == JoyStickLeftRight::Right)
	{
		reticlePos_.x = Input::GetJoyRStickPos().x;
		reticlePos_.y = Input::GetJoyRStickPos().y;
	}

	reticlePos_.x *= stickRad_;
	reticlePos_.y *= -stickRad_;

	//ï‚ä‘
	interTarget_ = Math::Vector::Lerp(interTarget_, reticlePos_, lerpFactor_);

	worldTransform_.transform.translate = Math::Vector::Add(worldTransform_.transform.translate, interTarget_);

	worldTransform_.UpdateMatrix();
}

void JoyStickUI::ImGuiUpdate()
{
}
