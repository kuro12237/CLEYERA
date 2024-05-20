#include "PlayerCamera.h"

void PlayerCamera::Initialize()
{
	cameraData_.Initialize();
	distinationAngleXY.x = 0.2f;
}

void PlayerCamera::Update()
{
	Math::Vector::Vector3 targetTranslate{};
	if (worldTransform_) {
		//t
		targetTranslate = worldTransform_->translate;
		//r
		//cameraData_.rotation_.y = worldTransform_->rotation.y;
		//cameraData_.rotation_.x = worldTransform_->rotation.x;
	}

	cameraData_.rotation_.x = distinationAngleXY.x;
	//cameraData_.rotation_.y += distinationAngleXY.y;

	Math::Matrix::Matrix4x4 rotateMatrix = Math::Matrix::RotateXYZMatrix(cameraData_.rotation_.x, cameraData_.rotation_.y, cameraData_.rotation_.z);
	Math::Vector::Vector3 offset = { 0.0f,1.0f,-24.0f };
	offset = Math::Vector::TransformNormal(offset, rotateMatrix);
	cameraData_.translation_ = Math::Vector::Add(targetTranslate, offset);

	cameraData_.UpdateMatrix();
}

void PlayerCamera::RotateMove()
{

}
