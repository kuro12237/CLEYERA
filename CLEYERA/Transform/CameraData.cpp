#include"CameraData.h"

void CameraData::Initialize(Vector3 r, Vector3 t)
{
	rotation_= r;
	translation_ = t;
	CreateBuffer();
	matProjection_ = MatrixTransform::PerspectiveFovMatrix(fov_, aspectRatio_, nearClip_, farClip_);
	OrthographicMatrix_ = MatrixTransform::OrthographicMatrix(0, 0, float(WinApp::GetkCilientWidth()), float(WinApp::GetkCilientHeight()), 0.0f, 100.0f);

}

void CameraData::UpdateMatrix()
{
	Matrix4x4 translateMatrix = MatrixTransform::TranslateMatrix(translation_);
	Matrix4x4 rotateXMatrix = MatrixTransform::RotateXMatrix(rotation_.x);
	Matrix4x4 rotateYMatrix = MatrixTransform::RotateYMatrix(rotation_.y);
	Matrix4x4 rotateZMatrix = MatrixTransform::RotateZMatrix(rotation_.z);
	Matrix4x4 rotateMatrix = MatrixTransform::Multiply(rotateXMatrix, MatrixTransform::Multiply(rotateYMatrix, rotateZMatrix));
	
	matView_ = MatrixTransform::Multiply(MatrixTransform::Inverse(translateMatrix), MatrixTransform::Inverse(rotateMatrix));
	matProjection_ = MatrixTransform::PerspectiveFovMatrix(fov_, aspectRatio_, nearClip_, farClip_);
	OrthographicMatrix_ = MatrixTransform::OrthographicMatrix(0, 0, float(WinApp::GetkCilientWidth()), float(WinApp::GetkCilientHeight()), 0.0f, 100.0f);

	TransfarMatrix();
}

void CameraData::CreateBuffer()
{
	buffer_ = make_shared<BufferResource<TransformationViewMatrix>>();
	buffer_->CreateResource(1);
}

void CameraData::Map()
{
	buffer_->Map();
}

void CameraData::UnMap()
{
	buffer_->UnMap();
}

void CameraData::TransfarMatrix()
{
	Map();

	BufferMatrix_.view = matView_;
	BufferMatrix_.viewProjection = matProjection_;
	BufferMatrix_.orthographic = OrthographicMatrix_;

	buffer_->Setbuffer(BufferMatrix_);

	Vector3 pos{};
	pos.x = matView_.m[3][0];
	pos.y = matView_.m[3][1];
	pos.z = matView_.m[3][2];

	BufferMatrix_.position = translation_;
	UnMap();
}
