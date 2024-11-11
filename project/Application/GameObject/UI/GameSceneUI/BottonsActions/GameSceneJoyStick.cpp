#include "GameSceneJoyStick.h"

void GameSceneJoyStick::Active(BaseBottonUI& ui)
{
	ui;
}

void GameSceneJoyStick::Inactive(BaseBottonUI& ui)
{
	ui;
}

void GameSceneJoyStick::Initialize(BaseBottonUI& ui)
{
	ui.AddJsonItem("stickRad", stickRad_);
	stickRad_ = ui.GetJsonItem<float>("stickRad");

	ui.AddJsonItem("lerpFactor", lerpFactor_);
	lerpFactor_ = ui.GetJsonItem<float>("lerpFactor");
}

void GameSceneJoyStick::Update(BaseBottonUI& ui)
{
	stickRad_ = ui.GetJsonItem<float>("stickRad");
	lerpFactor_ = ui.GetJsonItem<float>("lerpFactor");

	Math::Vector::Vector3 reticlePos_{};

	if (ui.GetUIEnum() == SceneUIEnum::JoyStick_L)
	{
		reticlePos_.x = Input::GetJoyLStickPos().x;
		reticlePos_.y = Input::GetJoyLStickPos().y;
	}
	if (ui.GetUIEnum() == SceneUIEnum::JoyStick_R)
	{
		reticlePos_.x = Input::GetJoyRStickPos().x;
		reticlePos_.y = Input::GetJoyRStickPos().y;
	}

	reticlePos_.x *= stickRad_;
	reticlePos_.y *= -stickRad_;

	TransformEular transform = ui.GetWorldTransform().transform;
	//ï‚ä‘
	interTarget_ = Math::Vector::Lerp(interTarget_, reticlePos_, lerpFactor_);

   transform.translate = Math::Vector::Add(transform.translate, interTarget_);

   ui.SetTransform(transform);

}

bool GameSceneJoyStick::IsLJoystickActive()
{
	return false;
}
