#include "PlayerCamera.h"

void PlayerCamera::Initialize()
{
	name_ = "PlayerCamera";
	transform_.scale = { 1.0f,1.0f,1.0f };
	transform_.translate.z = -32.0f;
}

void PlayerCamera::Update()
{

}
