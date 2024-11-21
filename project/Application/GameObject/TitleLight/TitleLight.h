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
	void SetP_CameraPos(const Math::Vector::Vector3& pos) { p_CameraPos_ = &pos; }
#pragma endregion

#pragma region Get

	Engine::Light::PointLight_param GetLightParam() { return light_; }

#pragma endregion

private:

	Engine::Light::PointLight_param light_ = {};

	const Math::Vector::Vector3* p_CameraPos_ = nullptr;

};