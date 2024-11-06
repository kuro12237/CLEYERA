#pragma once
#include"GameObject/ObjectInterface/ISpriteData.h"
#include"Input.h"
#include"GameObject/UI/GameSceneUIData.h"


/// <summary>
/// ジョイスティック背景2d表示クラス
/// </summary>
class JoyStickBackUI :public ISpriteData
{
public:
	JoyStickBackUI() {};
	~JoyStickBackUI() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initilaize(const string& groupName, const JoyStickLeftRight& direction);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	void ImGuiUpdate()override;


private:

};
