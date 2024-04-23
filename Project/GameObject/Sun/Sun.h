#pragma once
#include"Light/Light.h"
#include"Light/LightingManager.h"

class Sun
{
public:
	Sun() {};
	~Sun() {};

	void Initialize();

	void Update();

	void ImGuiUpdate();


private:

	PointLight_param param_{};

};