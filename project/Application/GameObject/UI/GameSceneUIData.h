#pragma once

/// <summary>
/// �Q�[���V�[���Ŏg��UI��
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
/// joyStick�̕�������肷��֐�
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