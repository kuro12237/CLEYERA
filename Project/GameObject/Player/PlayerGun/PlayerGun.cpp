#include "PlayerGun.h"

void PlayerGun::Initlalize()
{
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObjectDesc_.useLight = true;
	gameObject_->SetDesc(gameObjectDesc_);
	modelHandle_ = ModelManager::LoadObjectFile("PlayerGun");
	gameObject_->SetModel(modelHandle_);

	worldTransform_.Initialize();
	worldTransform_.translate.z = -3.0f;
}

void PlayerGun::Update()
{
	if (!reticlePos)
	{
		assert(0);
	}



	worldTransform_.UpdateMatrix();
}

void PlayerGun::Animation()
{
}

void PlayerGun::Draw(const CameraData& camera)
{
	camera;
	gameObject_->Draw(worldTransform_,camera);
}

void PlayerGun::Attack()
{

}
