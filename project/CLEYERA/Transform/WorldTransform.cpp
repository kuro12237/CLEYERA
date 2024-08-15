#include "WorldTransform.h"

using namespace Math::Vector;

void WorldTransform::CreateBuffer()
{
	buffer_ = make_shared<BufferResource<TransformationMatrix>>();
	buffer_->CreateResource(1);
}

void WorldTransform::Map()
{
	buffer_->Map();
}

void WorldTransform::UnMap()
{
	buffer_->UnMap();
}

void WorldTransform::Initialize()
{
	CreateBuffer();
	matWorld = Math::Matrix::Identity();
	TransfarMatrix();
}

void WorldTransform::SRTSetting(Vector3 s, Vector3 r, Vector3 t)
{
	transform.scale = s;
	transform.rotate = r;
	transform.translate = t;
	UpdateMatrix();
}

void WorldTransform::UpdateMatrix()
{
	matWorld = Math::Matrix::AffineMatrix(transform.scale, transform.rotate, transform.translate);

	if (parent) {
		matWorld = Math::Matrix::Multiply(matWorld, parent->matWorld);
	}
	TransfarMatrix();
}

void WorldTransform::TransfarMatrix()
{
	buffer_->Map();
	BufferMatrix_.WVP = matWorld;
	BufferMatrix_.world = matWorld;
	buffer_->Setbuffer(BufferMatrix_);
	buffer_->UnMap();
}


void WorldTransform::UpdateEularMatrix()
{
	matWorld = Math::Matrix::AffineMatrix(transform.scale, transform.rotate, transform.translate);

	if (parent) {
		matWorld = Math::Matrix::Multiply(matWorld, parent->matWorld);
	}

	TransfarMatrix();
}
//
//void WorldTransform::UpdateQuaternionMatrix()
//{
//	/*Math::Matrix::Matrix4x4 mScale = Math::Matrix::ScaleMatrix(scale);
//	Math::Matrix::Matrix4x4 mRotate = Math::Matrix::RotateXYZMatrix(rotation.x, rotation.y, rotation.z);
//	Math::Matrix::Matrix4x4 mTranslate = Math::Matrix::TranslateMatrix(translate);
//
//	Math::Matrix::Matrix4x4 mQuaternion = Math::Matrix::RotateMatrix(quaternion);
//	matWorld = Math::Matrix::Multiply(Math::Matrix::Multiply(mScale, mQuaternion), mTranslate);
//
//	if (parent) {
//		matWorld = Math::Matrix::Multiply(matWorld, parent->matWorld);
//	}*/
//}
//
//void WorldTransform::UpdateEularQuaternionMatrix()
//{
//
//	/*Math::Matrix::Matrix4x4 mScale = Math::Matrix::ScaleMatrix(scale);
//	Math::Matrix::Matrix4x4 mRotate = Math::Matrix::RotateXYZMatrix(rotation.x, rotation.y, rotation.z);
//	Math::Matrix::Matrix4x4 mTranslate = Math::Matrix::TranslateMatrix(translate);
//
//	Math::Matrix::Matrix4x4 mQuaternion = Math::Matrix::RotateMatrix(quaternion);
//
//	Math::Matrix::Matrix4x4 mEuler_Quaternion = Math::Matrix::Multiply(mRotate, mQuaternion);
//
//	matWorld = Math::Matrix::Multiply(Math::Matrix::Multiply(mScale, mEuler_Quaternion), mTranslate);
//
//	if (parent) {
//		matWorld = Math::Matrix::Multiply(matWorld, parent->matWorld);
//	}*/
//
//	TransfarMatrix();
//}

void WorldTransform::DeleateParent()
{
}

Vector3 WorldTransform::GetWorldPosition()
{
	return Vector3(matWorld.m[3][0], matWorld.m[3][1], matWorld.m[3][2]);
}
