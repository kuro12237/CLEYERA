#include "GameCameraData.h"

void GameCameraData::Create(TransformEular t)
{
	worldTransform_.Initialize();
	worldTransform_.rotation = t.rotate;
	worldTransform_.translate = t.translate;
	camera_.Initialize();
	camera_.UpdateMatrix();
}

void GameCameraData::WtUpdate(TransformEular transform)
{

	worldTransform_.scale = transform.scale;
	worldTransform_.rotation = transform.rotate;
	worldTransform_.translate = transform.translate;
	worldTransform_.UpdateMatrix();
}

void GameCameraData::Update()
{
	worldTransform_.UpdateMatrix();
	camera_.matView_ = Math::Matrix::Inverse(worldTransform_.matWorld);
	camera_.TransfarMatrix();
}
