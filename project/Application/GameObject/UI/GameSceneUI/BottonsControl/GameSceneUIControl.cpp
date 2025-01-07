#include "GameSceneUIControl.h"


using namespace Engine;
using namespace Engine::Objects;
using namespace Engine::Manager;
using namespace Engine::Transform;

bool GameSceneUIBottonsControl::ControlA()
{
	if (Input::PushBotton(XINPUT_GAMEPAD_A))
	{
		return true;
	}
    return false;
}

bool GameSceneUIBottonsControl::ControlRT()
{
	if (Input::PushRShoulder())
	{
		return true;
	}
	return false;
}

bool GameSceneUIBottonsControl::ControlRB()
{
	if (Input::PushBotton(XINPUT_GAMEPAD_RIGHT_SHOULDER))
	{
		return true;
	}
	return false;
}

