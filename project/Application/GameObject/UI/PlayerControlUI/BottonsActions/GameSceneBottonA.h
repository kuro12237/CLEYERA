#pragma once

#include"GameObject/UI/BaseSceneBottonUI/BaseBottonUI.h"
#include"Input.h"

/// <summary>
/// BottonA操作クラス
/// </summary>
class GameSceneUIBottonA
{
public:
	GameSceneUIBottonA() {};
	~GameSceneUIBottonA() {};


	bool ControlA();

	void Active(BaseBottonUI& ui);

	void Inactive(BaseBottonUI& ui);

private:

};
