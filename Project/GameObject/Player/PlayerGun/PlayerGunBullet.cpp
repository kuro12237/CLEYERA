#include "PlayerGunBullet.h"

void PlayerGunBullet::Initalize(const Math::Vector::Vector3& spownPos, const Math::Vector::Vector3& velocity)
{
	worldTransform_.Initialize();
	velocity_ = velocity;
	worldTransform_.translate = spownPos;

	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	modelHandle_ = ModelManager::LoadObjectFile("PlayerGunBullet");
	gameObject_->SetModel(modelHandle_);
	gameObjectDesc_={};
	gameObject_->SetDesc(gameObjectDesc_);

}

void PlayerGunBullet::Update()
{
	worldTransform_.translate = Math::Vector::Add(worldTransform_.translate, velocity_);
	worldTransform_.UpdateMatrix();
}

void PlayerGunBullet::Draw(const CameraData& camera)
{
	gameObject_->Draw(worldTransform_, camera);
}
