#include"PlayerGun.h"


using namespace Engine::Base::DX;
using namespace Engine::Base::Win;
using namespace Engine::Transform;
using namespace Engine::Objects;
using namespace Engine::Manager;

void PlayerGun::Initialize() {

	name_ = "PlayerGun";
	auto& transform =gameObjectManager_->GetObj3dData(name_)->GetWorldTransform().transform;
	transform.scale = { 1,1,1 };
}

void PlayerGun::Update()
{
	//基礎位置
	Math::Vector::Vector3 PlayerPos =gameObjectManager_->GetObj3dData("Player")->GetWorldTransform().transform.translate;
	PlayerPos.y += 1.5f;

	//銃のpos
	auto& transform = gameObjectManager_->GetObj3dData(name_)->GetWorldTransform();
	//銃からレティクルの補間
	Math::Vector::Vector3 reticleRotate = gameObjectManager_->GetObj3dData("PlayerReticle")->GetWorldTransform().transform.rotate;
	transform.transform.rotate = reticleRotate;
	//Math::Vector::Vector3 rotate = reticleRotate;


	Math::Vector::Vector2 Rjoy = Engine::Input::GetInstance()->GetJoyRStickPos();
	const float  joystickThreshold_ = 0.2f;
	if (std::abs(Rjoy.x) > joystickThreshold_ || std::abs(Rjoy.y) > joystickThreshold_) {
		Math::Vector::Vector2 normalizedRjoy_ = Math::Vector::Normalize(Rjoy);

		float kRetickeRad_ = 2.0f;
		// レティクルの位置を計算
		gunPos_ = {
			kRetickeRad_ * normalizedRjoy_.x,
			kRetickeRad_ * normalizedRjoy_.y
		};
	}
	else
	{
		Rjoy = {};
	}


	transform.transform.translate = Math::Vector::Add(PlayerPos, gunPos_);
}