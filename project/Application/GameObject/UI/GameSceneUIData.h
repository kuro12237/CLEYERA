#pragma once

/// <summary>
/// ゲームシーンで使うUI列挙
/// </summary>
enum class GameSceneUIEnum
{
	JoyStick_L,
	JoyStick_R,
};

enum class JoyStickLeftRight
{
	Left,
	Right,
};

/// <summary>
/// joyStickの方向を入手する関数
/// </summary>
/// <param name="direction"></param>
/// <returns></returns>
inline std::string CheckJoyStickUILeftRight(const JoyStickLeftRight& direction)
{
	if( direction == JoyStickLeftRight::Left)
	{
		return  "L";
	}
	if (direction == JoyStickLeftRight::Right)
	{
		return  "R";
	}
	return "";
}