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
	auto& transform = gameObjectManager_->GetObj3dData(name_)->GetWorldTransform().transform;
	//銃からレティクルの補間
	Math::Vector::Vector3 lerp = Math::Vector::Normalize(Math::Vector::Subtruct(*targetPos_, transform.translate));
	lerp = Math::Vector::Lerp(*targetPos_, transform.translate, 0.5f);
	//ベクトル
	Math::Vector::Vector3 Nlerp = Math::Vector::Normalize(lerp);

	Math::Vector::Vector3 resultPos = PlayerPos;

	transform.translate = resultPos;

	Math::Vector::Vector3 reticleRotate = gameObjectManager_->GetObj3dData("PlayerReticle")->GetWorldTransform().transform.rotate;
	transform.rotate = reticleRotate;
}