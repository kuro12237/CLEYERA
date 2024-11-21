#pragma once
#include"Sprite/Sprite.h"
#include"../ISceneUI.h"

#include"../BaseSceneBottonUI/BaseBottonUI.h"

#include"BottonsActions/GameSceneBottonsAction.h"
#include"BottonsControl/GameSceneUIControl.h"
#include"GameSceneUIData.h"
#include"BottonsActions/GameSceneJoyStick.h"


/// <summary>
/// ÉQÅ[ÉÄíÜÇÃUI
/// </summary>
class GameSceneUI :public ISceneUI
{
public:
	GameSceneUI() {};
	~GameSceneUI() {};

	/// <summary>
	/// èâä˙âª
	/// </summary>
	void Initialize()override;

private:

	unique_ptr<GameSceneUIBottonsAction>bottonAction_ = nullptr;
	unique_ptr<GameSceneUIBottonsControl>bottonControl_ = nullptr;
};
