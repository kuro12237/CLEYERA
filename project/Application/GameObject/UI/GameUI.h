#pragma once
#include"Sprite/Sprite.h"

/// <summary>
/// ゲーム中のUI
/// </summary>
class GameUI
{
public:
	GameUI() {};
	~GameUI() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 2d表示
	/// </summary>
	void Draw2d();

private:

	unique_ptr<Sprite>bottonASprite_ = nullptr;
	WorldTransform bottonAwT_ = {};
	uint32_t bottonATexhandle_ = 0;

};
