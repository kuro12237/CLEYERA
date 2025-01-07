#pragma once

/// <summary>
/// ゲームシーンで使うUI列挙
/// </summary>
enum class SceneUIEnum
{
	JoyStick_L,
	JoyStick_R,
	Botton_A,
	Botton_RT,
	Botton_RB,
	JoyStick_None,
};

/// <summary>
/// joyStickの方向を入手する関数
/// </summary>
/// <param name="direction"></param>
/// <returns></returns>
inline std::string CheckSceneUIEnumtoString(const SceneUIEnum& ui)
{
	if( ui == SceneUIEnum::JoyStick_L)
	{
		return  "L";
	}
	if (ui == SceneUIEnum::JoyStick_R)
	{
		return  "R";
	}
	if (ui==SceneUIEnum::Botton_A)
	{
		return "A";
	}
	if (ui == SceneUIEnum::Botton_RT)
	{
		return "RT";
	}
	if (ui == SceneUIEnum::Botton_RB)
	{
		return "RB";
	}
	return "";
}
