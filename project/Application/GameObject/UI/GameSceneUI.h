#pragma once
#include"Sprite/Sprite.h"
#include"ISceneUI.h"

#include"JoyUI/JoyStickUI.h"
#include"JoyUI/JoyStickBackUI.h"


struct JoyStickUIData
{
	string groupName = "";
	shared_ptr<JoyStickUI>stickUi = nullptr;
	shared_ptr<JoyStickBackUI>backUi = nullptr;
	
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="direction"></param>
	void Initialize(const JoyStickLeftRight& direction);
};


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

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// 2d表示
	/// </summary>
	void Draw2d()override;

private:

	uint32_t joyStickMax_ = 2;
	vector<JoyStickUIData>joyStickUis_;
};
