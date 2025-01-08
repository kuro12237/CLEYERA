#pragma once
#include"Sprite/Sprite.h"
#include"../ISceneUI.h"

#include"../BaseSceneBottonUI/BaseBottonUI.h"

#include"../PlayerControlUI/BottonsActions/GameSceneBottonsAction.h"
#include"GameSceneUIData.h"
#include"../PlayerControlUI/BottonsActions/GameSceneJoyStick.h"
#include"../PlayerControlUI/BottonsActions/GameSceneBottonRB.h"

/// <summary>
/// ゲーム中のUI
/// </summary>
class GameSceneUI :public ISceneUI
{
public:
	GameSceneUI() {};
	~GameSceneUI() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

private:

	unique_ptr<GameSceneUIBottonsAction>bottonAction_ = nullptr;
};
