#include "PlayerReticle.h"

void PlayerReticle::Initialize()
{
	worldTransform_.Initialize();

	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	uint32_t modelHandle = ModelManager::LoadObjectFile("TestBox");
	gameObject_->SetModel(modelHandle);
	gameObjectDesc_.useLight = false;
	gameObject_->SetDesc(gameObjectDesc_);

}

void PlayerReticle::Update()
{
	Math::Vector::Vector2 Rjoy = Input::GetJoyRStickPos();
	if (Rjoy.x >= -0.1f && Rjoy.x <= 0.1f)
	{
		Rjoy.x = {};
	}
	if (Rjoy.y >= -0.1f && Rjoy.y <= 0.1f)
	{
		Rjoy.y = {};
	}

	const float speed = 0.05f;
	joyPosition_.x = Rjoy.x * speed;
	joyPosition_.y = Rjoy.y * speed;

	worldTransform_.translate.x += joyPosition_.x;
	worldTransform_.translate.y += joyPosition_.y;

	worldTransform_.UpdateMatrix();
}

void PlayerReticle::Draw3d(const CameraData& camera)
{
	gameObject_->Draw(worldTransform_, camera);
}

void PlayerReticle::Draw2d(const CameraData& camera)
{
	camera;
}
