#pragma once

#include"GameObject/UI/BaseSceneBottonUI/BaseBottonUI.h"

/// <summary>
/// BottonRT操作クラス
/// </summary>
class GameSceneUIBottonRB
{
public:
	GameSceneUIBottonRB() {};
	~GameSceneUIBottonRB() {};

	void Active(BaseBottonUI& ui);

	void Inactive(BaseBottonUI& ui);


	bool ControlRB();
private:

};