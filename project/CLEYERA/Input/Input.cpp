#include"Input.h"

using namespace Math::Vector;
using namespace Engine::Base::Win;
using namespace Engine;

Input* Input::GetInstance()
{
	static Input instance;
	return &instance;
}

void Input::Initialize()
{
	HRESULT result{};
	if (Input::GetInstance()->isInitialize)
	{
		LogManager::Log("Input_Initialize_ERROR\n");
		assert(0);
	}

	//InputDevice
	result = DirectInput8Create(WinApp::GetInstance()->GetWc().hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&Input::GetInstance()->directInput, nullptr);

	assert(SUCCEEDED(result));
	
	CreateKeybordDevice();
	Input::GetInstance()->isInitialize = true;
}

void Input::BeginFlame()
{
	memcpy(Input::GetInstance()->preKeys, Input::GetInstance()->keys, 256);
	Input::GetInstance()->keyboard->Acquire();
	Input::GetInstance()->keyboard->GetDeviceState(sizeof(Input::GetInstance()->keys), Input::GetInstance()->keys);

	//前のゲームパッドの状態をコピー
	Input::GetInstance()->preJoyState_ = Input::GetInstance()->joyState_;
	Input::GetInstance()->moterFlame_ ++;
	if (Input::GetInstance()->moterFlame_>Input::GetInstance()->moterFlameMax_)
	{
		std::memset(&Input::GetInstance()->vibration_, 0, sizeof(XINPUT_VIBRATION));
		// Set the vibration levels
		Input::GetInstance()->vibration_.wLeftMotorSpeed = WORD(0);
		Input::GetInstance()->vibration_.wRightMotorSpeed = WORD(0);
		Input::GetInstance()->leftMotor_ = 0;
		Input::GetInstance()->rightMotor_ = 0;
		Input::GetInstance()->isMoter_ = false;;
	}

	XInputSetState(0, &Input::GetInstance()->vibration_);
	//今のゲームパッドを更新
    GetJoystickState();
}

bool Input::PushKeyPressed(uint32_t keyNum)
{
	if (Input::GetInstance()->keys[keyNum] == 0x80 && Input::GetInstance()->preKeys[keyNum]==0x00)
	{
		return true;
	}
	return false;
}

bool Input::GetJoystickState()
{
	DWORD dwResult = XInputGetState(0, &Input::GetInstance()->joyState_);
	if (dwResult == ERROR_SUCCESS) {
		return true;
	}
	return false;
}

bool Input::PushBottonPressed(uint32_t GameBotton)
{
	bool preFlag = false;

	if (Input::GetInstance()->preJoyState_.Gamepad.wButtons & GameBotton)
	{
		preFlag = true;
	}

	if (!preFlag && Input::GetInstance()->joyState_.Gamepad.wButtons & GameBotton)
	{
		return true;
	}

	return false;
}


bool Input::PushBotton(uint32_t GameBotton)
{

	if (Input::GetInstance()->joyState_.Gamepad.wButtons & GameBotton)
	{
		return true;
	}
	return false;
}

bool Input::PushLShoulder()
{
	if (Input::GetInstance()->joyState_.Gamepad.bLeftTrigger)
	{
		return true;
	}

	return false;
}

bool Input::PushLShoulderPressed()
{
	if (!Input::GetInstance()->preJoyState_.Gamepad.bLeftTrigger && Input::GetInstance()->joyState_.Gamepad.bLeftTrigger)
	{
		return true;
	}

	return false;
}

bool Input::PushRShoulder()
{
	if (Input::GetInstance()->joyState_.Gamepad.bRightTrigger)
	{
		return true;
	}

	return false;
}

bool Input::PushRShoulderPressed()
{
	if (!Input::GetInstance()->preJoyState_.Gamepad.bRightTrigger && Input::GetInstance()->joyState_.Gamepad.bRightTrigger)
	{
		return true;
	}

	return false;
}

Vector2 Input::GetJoyLStickPos(const float &mode)
{
	float deadzone = Input::GetInstance()->deadzone_;

	Math::Vector::Vector2 joyPos(
		Input::GetInstance()->joyState_.Gamepad.sThumbLX / mode,
	    Input::GetInstance()->joyState_.Gamepad.sThumbLY / mode
	);

	if (std::abs(joyPos.x) > deadzone || std::abs(joyPos.y) > deadzone)
	{
		return joyPos;
	}
	return {};
}

bool Input::GetLJoyTHUMB()
{
	if (Input::GetInstance()->joyState_.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
	{
		return true;
	}
	return false;
}

Vector2 Input::GetJoyRStickPos(const float& mode)
{
	float deadzone = Input::GetInstance()->deadzone_;
	Math::Vector::Vector2 joyPos(
		Input::GetInstance()->joyState_.Gamepad.sThumbRX / mode,
		Input::GetInstance()->joyState_.Gamepad.sThumbRY / mode
	);

	if (std::abs(joyPos.x) > deadzone || std::abs(joyPos.y) > deadzone)
	{
		return joyPos;
	}

	return {};
}

bool Engine::Input::GetJoyRActive(const float& mode)
{
	float deadzone = Input::GetInstance()->deadzone_;
	Math::Vector::Vector2 joyPos(
		Input::GetInstance()->joyState_.Gamepad.sThumbRX / mode,
		Input::GetInstance()->joyState_.Gamepad.sThumbRY / mode
	);

	if (std::abs(joyPos.x) > deadzone || std::abs(joyPos.y) > deadzone)
	{
		return true;;
	}

	return false;
}

bool Engine::Input::GetJoyLActive(const float& mode)
{
	float deadzone = Input::GetInstance()->deadzone_;
	Math::Vector::Vector2 joyPos(
		Input::GetInstance()->joyState_.Gamepad.sThumbLX / mode,
		Input::GetInstance()->joyState_.Gamepad.sThumbLY / mode
	);

	if (std::abs(joyPos.x) > deadzone || std::abs(joyPos.y) > deadzone)
	{
		return true;
	}

	return false;
}

bool Input::GetRJoyTHUMB()
{
	if (Input::GetInstance()->joyState_.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
	{
		return true;
	}
	return false;
}

void Input::VibrateController(int leftMotor, int rightMotor,float max)
{
	Input::GetInstance()->moterFlameMax_ = max;
	Input::GetInstance()->moterFlame_ = 0.0f;
	Input::GetInstance()->isMoter_ = true;
	Input::GetInstance()->leftMotor_ = WORD(leftMotor);
	Input::GetInstance()->rightMotor_ = WORD(rightMotor);

	std::memset(&Input::GetInstance()->vibration_, 0, sizeof(XINPUT_VIBRATION));

	// Set the vibration levels
	Input::GetInstance()->vibration_.wLeftMotorSpeed = WORD(leftMotor); 
	Input::GetInstance()->vibration_.wRightMotorSpeed = WORD(rightMotor); 

}

void Input::CreateKeybordDevice()
{
	HRESULT hr{};
	Input::GetInstance()->directInput->CreateDevice(GUID_SysKeyboard,
		&Input::GetInstance()->keyboard, NULL);
	assert(SUCCEEDED(hr));
	//���̓f�[�^�`���̃Z�b�g
	hr = Input::GetInstance()->keyboard->SetDataFormat(&c_dfDIKeyboard);
	assert(SUCCEEDED(hr));
	//
	hr = Input::GetInstance()->keyboard->SetCooperativeLevel(
		WinApp::GetHwnd(),
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY
	);

}

bool Input::PushKey(uint8_t keyNum)
{
	if (Input::GetInstance()->keys[keyNum] == 0x80)
	{
		return true;
	}
	return false;
}