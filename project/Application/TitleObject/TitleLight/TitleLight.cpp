#include "TitleLight.h"

void TitleLight::Initialize()
{
	light_.radious = 512.0f;
	light_.position.y = 64.0f;
	light_.position.z = -16.0f;
	light_.decay = 0.1f;
}

void TitleLight::Update()
{
	LightingManager::AddList(light_);
}
