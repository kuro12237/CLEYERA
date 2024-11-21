#include "GameCameraData.h"

using namespace Engine;
using namespace Engine::Transform;

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
	camera_.translation_ = worldTransform_.transform.translate;
	camera_.rotation_ = worldTransform_.transform.rotate;
	camera_.matView_ = Math::Matrix::Inverse(worldTransform_.matWorld);
	camera_.TransfarMatrix();
}
