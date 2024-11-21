#pragma once
#include"Light/LightingManager.h"

/// <summary>
/// �^�C�g���̃��C�g
/// </summary>
class TitleLight
{
public:
	TitleLight() {};
	~TitleLight() {};

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
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