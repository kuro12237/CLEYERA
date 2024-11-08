#pragma once
#include"Sprite/Sprite.h"
#include"../ISceneUI.h"

#include"../BaseSceneBottonUI/BaseBottonUI.h"



/// <summary>
/// タイトル中のUI
/// </summary>
class TitleSceneUI :public ISceneUI
{
public:
	TitleSceneUI() {};
	~TitleSceneUI() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

private:

};