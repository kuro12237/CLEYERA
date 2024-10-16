#pragma once
#include"Sprite/Sprite.h"

/// <summary>
/// タイトル3dのクラス
/// </summary>
class TitleName
{
public:
	TitleName() {};
	~TitleName() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:

	unique_ptr<Engine::Objects::Sprite>sprite_ = nullptr;
	Engine::Transform::WorldTransform worldTransform_ = {};
	uint32_t texHandle_ = 0;

};
