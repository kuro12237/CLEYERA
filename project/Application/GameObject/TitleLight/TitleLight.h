#pragma once
#include"Light/LightingManager.h"

/// <summary>
/// タイトルのライト
/// </summary>
class TitleLight
{
public:
	TitleLight() {};
	~TitleLight() {};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

#pragma region Set
	void SetPos(const Math::Vector::Vector3& pos) { light_.position = pos; }
#pragma endregion

#pragma region Get

	PointLight_param GetLightParam() { return light_; }

#pragma endregion

private:

	PointLight_param light_ = {};

};