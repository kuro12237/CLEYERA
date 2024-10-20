#include"PlayerGun.h"

void PlayerGun::Initialize() {

	name_ = "PlayerGun";

	auto& transform = GameObjectManager::GetInstance()->GetObj3dData(name_)->GetWorldTransform().transform;
	transform.scale = { 1,1,1 };
}

void PlayerGun::Update()
{
	Math::Vector::Vector3 targetPos = GameObjectManager::GetInstance()->GetObj3dData("Player")->GetWorldTransform().transform.translate;
	targetPos.y += 1.5f;
	Math::Vector::Vector3 worldPos = GameObjectManager::GetInstance()->GetObj3dData(name_)->GetWorldTransform().GetWorldPosition();
	Math::Vector::Vector3 lerp = Math::Vector::Normalize(Math::Vector::Subtruct(targetPos_, worldPos));

	Math::Vector::Vector3 Nlerp = Math::Vector::Normalize(lerp);
	Math::Vector::Vector3 rotate = {};

	float rotateXZ = sqrt(pow(Nlerp.x, 2.0f) + pow(Nlerp.z, 2.0f));
	float height = -Nlerp.y;

	if (rotateXZ != 0.0f) {
		rotate.y = std::acos(Nlerp.z / rotateXZ);
		if (Nlerp.x < 0) {
			rotate.y = -rotate.y;
		}
	}
	else {
		rotate.y = 0.0f;
	}

	rotate.x = std::asin(height / sqrt(pow(height, 2.0f) + pow(rotateXZ, 2.0f)));

	auto& transform = GameObjectManager::GetInstance()->GetObj3dData(name_)->GetWorldTransform().transform;
	transform.rotate = rotate;
	transform.translate = targetPos;
}