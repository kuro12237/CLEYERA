#include"CameraData.h"

using namespace Math::Matrix;
using namespace Math::Vector;

using namespace Engine::Base::DX;
using namespace Engine::Base::Win;
using namespace Engine::Camera;

void CameraData::Initialize(Vector3 r, Vector3 t)
{
	rotation_ = r;
	translation_ = t;
	CreateBuffer();
	matProj_ = Math::Matrix::PerspectiveFovMatrix(fov_, aspectRatio_, nearClip_, farClip_);
	OrthographicMatrix_ = Math::Matrix::OrthographicMatrix(0, 0, float(WinApp::GetkCilientWidth()), float(WinApp::GetkCilientHeight()), 0.0f, 100.0f);
	matView_ = Math::Matrix::Identity();
	matProjInverse_ = Math::Matrix::Identity();
	matVPInverse_ = Math::Matrix::Identity();
}

void CameraData::UpdateMatrix()
{
	Matrix4x4 translateMatrix = Math::Matrix::TranslateMatrix(translation_);
	Matrix4x4 rotateXMatrix = Math::Matrix::RotateXMatrix(rotation_.x);
	Matrix4x4 rotateYMatrix = Math::Matrix::RotateYMatrix(rotation_.y);
	Matrix4x4 rotateZMatrix = Math::Matrix::RotateZMatrix(rotation_.z);
	Matrix4x4 rotateMatrix = Math::Matrix::Multiply(rotateXMatrix, Math::Matrix::Multiply(rotateYMatrix, rotateZMatrix));

	matView_ = Math::Matrix::Multiply(Math::Matrix::Inverse(translateMatrix), Math::Matrix::Inverse(rotateMatrix));
	matProj_ = Math::Matrix::PerspectiveFovMatrix(fov_, aspectRatio_, nearClip_, farClip_);
	OrthographicMatrix_ = Math::Matrix::OrthographicMatrix(0, 0, float(WinApp::GetkCilientWidth()), float(WinApp::GetkCilientHeight()), 0.0f, 100.0f);

	TransfarMatrix();
}

void CameraData::CreateBuffer()
{
	buffer_ = make_shared<BufferResource<TransformationViewMatrix>>();
	buffer_->CreateResource(1);

	psBuffer_ = make_shared<BufferResource<TransformationViewMatrix>>();
	psBuffer_->CreateResource(1);
}

void CameraData::Map()
{
	buffer_->Map();
	psBuffer_->Map();
}

void CameraData::UnMap()
{
	buffer_->UnMap();
	psBuffer_->UnMap();
}

void CameraData::TransfarMatrix()
{
	Map();

	matVP_ = Math::Matrix::Multiply(matView_, matProj_);
	matVPInverse_ = Math::Matrix::Inverse(matVP_);
	matProjInverse_ = Math::Matrix::Inverse(matProj_);

	BufferMatrix_.view = matView_;
	BufferMatrix_.viewProjection = matProj_;
	BufferMatrix_.orthographic = OrthographicMatrix_;
	BufferMatrix_.position = translation_;
	BufferMatrix_.InverseViewProjection = matVPInverse_;;
	BufferMatrix_.InverseProjection = matProjInverse_;

	buffer_->Setbuffer(BufferMatrix_);
	psBuffer_->Setbuffer(BufferMatrix_);
	UnMap();
}
