#include "GameCameraData.h"

void GameCameraData::Create(TransformEular t)
{
	worldTransform_.Initialize();
	worldTransform_.transform.rotate = t.rotate;
	worldTransform_.transform.translate = t.translate;
	camera_.Initialize();
	camera_.UpdateMatrix();
}

void GameCameraData::WtUpdate(TransformEular transform)
{

	worldTransform_.transform = transform;
	worldTransform_.UpdateMatrix();
}

void GameCameraData::Update()
{
	worldTransform_.UpdateMatrix();
	camera_.matView_ = Math::Matrix::Inverse(worldTransform_.matWorld);
	camera_.TransfarMatrix();
}