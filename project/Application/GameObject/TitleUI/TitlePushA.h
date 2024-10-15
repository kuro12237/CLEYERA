#pragma once
#include"Sprite/Sprite.h"

/// <summary>
/// TitleのPushAボタン
/// </summary>
class TitlePushA
{
public:
	TitlePushA() {};
	~TitlePushA() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initiaize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 表示
	/// </summary>
	void Draw();

private:

	unique_ptr<Sprite>sprite_ = nullptr;
	WorldTransform worldTransform_ = {};
	uint32_t texhandle_ = 0;

	const float kScale_= 0.75f;
	Math::Vector::Vector3 pos_ = { 640.0f,618.0f,0.0f };
};
