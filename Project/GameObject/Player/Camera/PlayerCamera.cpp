#include "PlayerCamera.h"

void PlayerCamera::Initialize()
{
	cameraData_.Initialize();
}

void PlayerCamera::Update()
{
	Vector3 targetTranslate{};
	if (worldTransform_) {
		//t
		targetTranslate = worldTransform_->translate;
		//r
        cameraData_.rotation_.y = worldTransform_->rotation.y;
		cameraData_.rotation_.x = worldTransform_->rotation.x;
	}

	RotateMove();
	cameraData_.rotation_.x += distinationAngleXY.x;
	cameraData_.rotation_.y += distinationAngleXY.y;

	Matrix4x4 rotateMatrix = MatrixTransform::RotateXYZMatrix(cameraData_.rotation_.x, cameraData_.rotation_.y, cameraData_.rotation_.z);
	Vector3 offset = { 0.0f,1.0f,-32.0f };
	offset = VectorTransform::TransformNormal(offset, rotateMatrix);
	cameraData_.translation_ = VectorTransform::Add(targetTranslate, offset);

	cameraData_.UpdateMatrix();
}

void PlayerCamera::RotateMove()
{
	Vector2 Rjoy = Input::GetJoyRStickPos();
	float Length = VectorTransform::Length(Vector3(Rjoy.x, Rjoy.y, 0.0f));
	if (Length <= 0.1f)
	{
		Rjoy = {};
	}

	const float speed = 0.05f;
	Vector2 rotate = { Rjoy.x * -speed,Rjoy.y * speed };

    distinationAngleXY.y += rotate.x;
    distinationAngleXY.x += rotate.y;

}
