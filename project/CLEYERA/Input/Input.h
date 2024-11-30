#pragma once
#include"Pch.h"
#include"WinApp.h"
#include"LogManager.h"

namespace Engine
{

	/// <summary>
	/// コントローラーとキーボードの入力を取得
	/// </summary>
	class Input
	{
	public:

		static Input* GetInstance();

		/// <summary>
		/// 初期化
		/// </summary>
		static void Initialize();

		/// <summary>
		/// 毎フレームの始まり
		/// </summary>
		static void BeginFlame();

		/// <summary>
		/// 押されているか
		/// </summary>
		/// <param name="keyNum"></param>
		/// <returns></returns>
		static bool PushKey(uint8_t keyNum);

		/// <summary>
		/// 一瞬　押したか
		/// </summary>
		static bool PushKeyPressed(uint32_t keyNum);

		/// <summary>
		/// コントローラーがつながっているか
		/// </summary>
		/// <returns></returns>
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
		static Math::Vector::Vector2 GetJoyLStickPos(const float& mode = SHRT_MAX);

		/// <summary>
		/// Lsyic押し込み検知
		/// </summary>
		/// <returns></returns>
		static bool GetLJoyTHUMB();

		/// <summary>
		/// Rstic
		/// </summary>
		/// <param name="mode"></param>
		/// <returns></returns>
		static Math::Vector::Vector2 GetJoyRStickPos(const float& mode = SHRT_MAX);

		static bool GetJoyRActive(const float& mode = SHRT_MAX);
		static bool GetJoyLActive(const float& mode = SHRT_MAX);

		/// <summary>
		/// Lsyic押し込み検知
		/// </summary>
		/// <returns></returns>
		static bool GetRJoyTHUMB();

		/// <summary>
		/// コントローラーの倍部
		/// </summary>
		/// <param name="leftMotor"></param>
		/// <param name="rightMotor"></param>
		/// <param name="max"></param>
		static void VibrateController(int leftMotor, int rightMotor, float max = 60.0f);

		/// <summary>
		/// デッドゾーンの設定
		/// </summary>
		/// <param name="deadzone"></param>
		static void SetDeadZone(float deadzone) { Input::GetInstance()->deadzone_ = deadzone; }

	private:

		/// <summary>
		/// keybordの読み込みデバイス作成
		/// </summary>
		static void CreateKeybordDevice();

		ComPtr<IDirectInput8> directInput = nullptr;
		ComPtr<IDirectInputDevice8> keyboard = nullptr;

		BYTE keys[256] = {};
		BYTE preKeys[256] = {};

		XINPUT_STATE joyState_{};
		XINPUT_STATE preJoyState_{};
		XINPUT_VIBRATION vibration_;
		WORD rightMotor_ = 0;
		WORD leftMotor_ = 0;
		float moterFlame_ = 0.0f;
		float moterFlameMax_ = 30.0f;
		bool isMoter_ = false;

		bool isInitialize = false;

		float deadzone_ = 0.0f;

		Input() = default;
		~Input() = default;
		Input(const Input&) = delete;
		const Input& operator=(const Input&) = delete;
	};

}