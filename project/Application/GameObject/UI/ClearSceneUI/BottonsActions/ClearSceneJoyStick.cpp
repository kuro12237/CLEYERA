#include "ClearSceneJoyStick.h"


void ClearSceneJoyStick::Initialize(const string& groupName, const SceneUIEnum& ui)
{
	this->CreateUIData(groupName, ui);
}

void ClearSceneJoyStick::Update(BaseBottonUI& ui)
{
	flame_ += 1.0f / 30.0f;
	isActionFlag_ = false;

	ui;
	if (flame_ >= 1.0f)
	{
		if (IsLJoystickActive())
		{
			isActionFlag_ = true;
			flame_ = 0.0f;
		}
	}

}

bool ClearSceneJoyStick::IsLJoystickActive()
{
	float joystickThreshold = 0.2f;
	Math::Vector::Vector2 Ljoy = Engine::Input::GetInstance()->GetJoyLStickPos();
	if (std::abs(Ljoy.x) > joystickThreshold || std::abs(Ljoy.y) > joystickThreshold) {

		return true;
	}
	return false;
}
