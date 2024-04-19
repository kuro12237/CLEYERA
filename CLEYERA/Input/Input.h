#pragma once
#include"Pch.h"
#include"WinApp.h"
#include"LogManager.h"

class Input
{
public:


	static Input * GetInstance();

	static void Initialize();

	static void BeginFlame();

	static bool PushKey(uint8_t keyNum);

	static bool PushKeyPressed(uint32_t keyNum);

	
	static bool GetJoystickState();

	/// <summary>
	/// ボタンのトリガー
	/// </summary>
	/// <param name="GameBotton"></param>
	/// <returns></returns>
	static bool PushBottonPressed(uint32_t GameBotton);

	/// <summary>
	/// ボタン押し続けてる
	/// </summary>
	/// <param name="GameBotton"></param>
	/// <returns></returns>
	static bool PushBotton(uint32_t GameBotton);

	/// <summary>
	/// ZL押し続ける
	/// </summary>
	/// <param name="mode"></param>
	/// <returns></returns>
	static bool PushLShoulder();

	/// <summary>
    /// ZL一瞬
    /// </summary>
    /// <param name="mode"></param>
    /// <returns></returns>
	static bool PushLShoulderPressed();


	/// <summary>
	/// ZR押し続ける
	/// </summary>
	/// <param name="mode"></param>
	/// <returns></returns>
	static bool PushRShoulder();

	/// <summary>
	/// ZR一瞬
	/// </summary>
	/// <param name="mode"></param>
	/// <returns></returns>
	static bool PushRShoulderPressed();


	/// <summary>
	/// Lstic
	/// </summary>
	/// <param name="mode"></param>
	/// <returns></returns>
	static Math::Vector::Vector2 GetJoyLStickPos(const float &mode = SHRT_MAX);

	/// <summary>
    /// Rstic
    /// </summary>
    /// <param name="mode"></param>
    /// <returns></returns>
	static Math::Vector::Vector2 GetJoyRStickPos(const float& mode = SHRT_MAX);


private:

	static void CreateKeybordDevice();

	ComPtr<IDirectInput8> directInput = nullptr;
	ComPtr<IDirectInputDevice8> keyboard = nullptr;

	BYTE keys[256] = {};
	BYTE preKeys[256] = {};

	XINPUT_STATE joyState_{};
	XINPUT_STATE preJoyState_{};

	bool isInitialize=false;


	Input() = default;
	~Input() = default;
	Input(const Input&) = delete;
	const Input& operator=(const Input&) = delete;
};

