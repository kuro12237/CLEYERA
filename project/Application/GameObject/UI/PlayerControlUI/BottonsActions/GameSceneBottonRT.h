#pragma once
#include"GameObject/UI/BaseSceneBottonUI/BaseBottonUI.h"

/// <summary>
/// BottonRT操作クラス
/// </summary>
class GameSceneUIBottonRT
{
public:
	GameSceneUIBottonRT() {};
	~GameSceneUIBottonRT() {};

	void Active(BaseBottonUI& ui);

	void Inactive(BaseBottonUI& ui);

	bool ControlRT();
private:

};