#pragma once


#include"Sprite/Sprite.h"
#include"../ISceneUI.h"

#include"../BaseSceneBottonUI/BaseBottonUI.h"

#include"../PlayerControlUI/BottonsActions/GameSceneBottonsAction.h"

/// <summary>
/// ゲームオーバー中のUI
/// </summary>
class GameOverSceneUI :public ISceneUI
{
public:
	GameOverSceneUI() {};
	~GameOverSceneUI() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

private:

};
