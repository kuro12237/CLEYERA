#include "PlayerReticle.h"

void PlayerReticle::Initialize()
{
	worldTransform_.Initialize();

	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	uint32_t modelHandle = ModelManager::LoadObjectFile("PlayerReticle");
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

	const float speed = 0.1f;
	joyPosition_.x = Rjoy.x * speed;
	joyPosition_.y = Rjoy.y * speed;

	worldTransform_.translate.x += joyPosition_.x;
	worldTransform_.translate.y += joyPosition_.y;

	const float kDistancePlayerTo3DReticle = 40.0f;
	Math::Vector::Vector3 offset = { joyPosition_.x, joyPosition_.y, 0.0f };

	offset = Math::Vector::TransformNormal(offset, worldTransform_.matWorld);
	offset =  Math::Vector::Normalize(offset);
	offset =  Math::Vector::Multiply(offset, kDistancePlayerTo3DReticle);

	worldTransform_.rotation = { joyPosition_.x,joyPosition_.y,0.0f };

	//worldTransform_.translate = offset;//Math::Vector::Add(offset,worldTransform_.translate);
	vecPos_ = offset;

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
