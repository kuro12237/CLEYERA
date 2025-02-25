#pragma once
#include"GameObject/ObjectInterface/ISpriteData.h"


class GameOverText:public ISpriteData
{
public:
	GameOverText() {};
	~GameOverText() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	void ImGuiUpdate()override;

private:

	float flame_ = 0.0f;
	float flameMax_ = 1.0f;

	float scaleMax_ = 0.5f;

};