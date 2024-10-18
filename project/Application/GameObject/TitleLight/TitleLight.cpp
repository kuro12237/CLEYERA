#include "TitleLight.h"

using namespace Engine::Manager;

void TitleLight::Initialize()
{
	light_.radious = 512.0f;
	light_.position.y = 64.0f;
	light_.position.z = -16.0f;
	light_.decay = 0.1f;

	light_.position.y = 16.0f;
}

void TitleLight::Update()
{
	light_.position.z = p_CameraPos_->z;

	LightingManager::AddList(light_);
}
