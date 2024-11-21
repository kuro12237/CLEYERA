#include "ClearSceneUIControl.h"

bool ClearSceneUIBottonsControl::ControlA()
{
	if (Engine::Input::PushBotton(XINPUT_GAMEPAD_A))
	{
		return true;
	}
    return false;
}

