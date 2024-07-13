#include "PlayerCamera.h"

void PlayerCamera::Initialize()
{
	name_ = "PlayerCamera";

	auto& transform = GameObjectManager::GetInstance()->GetCameraData(name_)->GetWorldTransform().transform;
	transform.scale = { 1.0f,1.0f,1.0f };
	transform.translate.z = -32.0f;
}

void PlayerCamera::Update()
{

}
