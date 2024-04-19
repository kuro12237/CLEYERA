#include"CameraData.h"

using namespace Math::Matrix;
using namespace Math::Vector;

void CameraData::Initialize(Vector3 r, Vector3 t)
{
	rotation_= r;
	translation_ = t;
	CreateBuffer();
	matProjection_ = Math::Matrix::PerspectiveFovMatrix(fov_, aspectRatio_, nearClip_, farClip_);
	OrthographicMatrix_ = Math::Matrix::OrthographicMatrix(0, 0, float(WinApp::GetkCilientWidth()), float(WinApp::GetkCilientHeight()), 0.0f, 100.0f);

}

void CameraData::UpdateMatrix()
{
	Matrix4x4 translateMatrix = Math::Matrix::TranslateMatrix(translation_);
	Matrix4x4 rotateXMatrix = Math::Matrix::RotateXMatrix(rotation_.x);
	Matrix4x4 rotateYMatrix = Math::Matrix::RotateYMatrix(rotation_.y);
	Matrix4x4 rotateZMatrix = Math::Matrix::RotateZMatrix(rotation_.z);
	Matrix4x4 rotateMatrix = Math::Matrix::Multiply(rotateXMatrix, Math::Matrix::Multiply(rotateYMatrix, rotateZMatrix));
	
	matView_ = Math::Matrix::Multiply(Math::Matrix::Inverse(translateMatrix), Math::Matrix::Inverse(rotateMatrix));
	matProjection_ = Math::Matrix::PerspectiveFovMatrix(fov_, aspectRatio_, nearClip_, farClip_);
	OrthographicMatrix_ = Math::Matrix::OrthographicMatrix(0, 0, float(WinApp::GetkCilientWidth()), float(WinApp::GetkCilientHeight()), 0.0f, 100.0f);

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
	BufferMatrix_.position = translation_;
	BufferMatrix_.InverseViewProjection = Math::Matrix::Inverse((Math::Matrix::Multiply(BufferMatrix_.viewProjection, BufferMatrix_.view)));
	BufferMatrix_.InverseProjection = Math::Matrix::Inverse(BufferMatrix_.viewProjection);

	buffer_->Setbuffer(BufferMatrix_);
	UnMap();
}
