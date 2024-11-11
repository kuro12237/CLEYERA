#include "ClearSceneUIControl.h"

bool ClearSceneUIBottonsControl::ControlA()
{
	if (Input::PushBotton(XINPUT_GAMEPAD_A))
	{
		return true;
	}
    return false;
}

