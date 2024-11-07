#pragma once

/// <summary>
/// �Q�[���V�[���Ŏg��UI��
/// </summary>
enum class SceneUIEnum
{
	JoyStick_L,
	JoyStick_R,
	Botton_A,
	Botton_RT,
	JoyStick_None,
};

/// <summary>
/// joyStick�̕�������肷��֐�
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
	return "";
}
