#include "GameSceneUIControl.h"

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

