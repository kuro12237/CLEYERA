#include"PlayerGun.h"


using namespace Engine::Base::DX;
using namespace Engine::Base::Win;
using namespace Engine::Transform;
using namespace Engine::Objects;
using namespace Engine::Manager;

void PlayerGun::Initialize() {

	name_ = "PlayerGun";
	auto& transform = gameObjectManager_->GetObj3dData(name_)->GetWorldTransform().transform;
	transform.scale = { 1.0f,1.0f,1.0f };
	Math::Vector::Vector3 playerRotate = gameObjectManager_->GetObj3dData("Player")->GetWorldTransform().transform.rotate;

	gunPos_.x = kRadious_;

}

void PlayerGun::Update()
{

	//基礎位置
	auto playerCore = player_.lock();
	const float offset = 1.5f;
	Math::Vector::Vector3 PlayerPos = playerCore->GetObjectData().lock()->GetWorldTransform().transform.translate;
	Math::Vector::Vector3 playerRotate = gameObjectManager_->GetObj3dData("Player")->GetWorldTransform().transform.rotate;

	PlayerPos.y += offset;

	//銃のpos
	auto& transform = gameObjectManager_->GetObj3dData(name_)->GetWorldTransform();

	if (playerCore->IsInState<PlayerStateDeadAnimation>())
	{
		SetIsDraw(false);
	}

	if (playerCore->IsInState<PlayerStateAim>())
	{
		Math::Vector::Vector2 Rjoy = Engine::Input::GetInstance()->GetJoyRStickPos();
		Math::Vector::Vector2 normalizedRjoy_ = Math::Vector::Normalize(Rjoy);

		// レティクルの位置を計算
		gunPos_ = {
			kRadious_ * normalizedRjoy_.x,
			kRadious_ * normalizedRjoy_.y
		};
	}
	else
	{
		const float degree = 90.0f;
		gunPos_.y = 0.0f;
		if (playerRotate.y >= Math::Vector::degreesToRadians(degree))
		{
			gunPos_.x = kRadious_ * 1.0f;
		}
		if (playerRotate.y <= -Math::Vector::degreesToRadians(degree))
		{
			gunPos_.x = kRadious_ * -1.0f;
		}
	
	}

	//レティクルのと同じ角度に
	Math::Vector::Vector3 reticleRotate = gameObjectManager_->GetObj3dData("PlayerReticle")->GetWorldTransform().transform.rotate;
	transform.transform.rotate = reticleRotate;
	transform.transform.translate = Math::Vector::Add(PlayerPos, gunPos_);
}