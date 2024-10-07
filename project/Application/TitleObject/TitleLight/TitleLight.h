#pragma once
#include"Light/LightingManager.h"

class TitleLight
{
public:
	TitleLight() {};
	~TitleLight() {};

	void Initialize();

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