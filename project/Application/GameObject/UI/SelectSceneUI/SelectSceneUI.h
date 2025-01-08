#pragma once
#pragma once
#include"Sprite/Sprite.h"
#include"../ISceneUI.h"

#include"../BaseSceneBottonUI/BaseBottonUI.h"

#include"../PlayerControlUI/BottonsActions/GameSceneBottonsAction.h"

/// <summary>
/// ゲーム中のUI
/// </summary>
class SelectSceneUI :public ISceneUI
{
public:
	SelectSceneUI() {};
	~SelectSceneUI() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

private:

	unique_ptr<GameSceneUIBottonsAction>bottonAction_ = nullptr;
};
