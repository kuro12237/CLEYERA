#include "WorldTransform.h"

using namespace Math::Vector;
using namespace Engine::Transform;


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
	BufferMatrix_.worldPos = GetWorldPosition();
	buffer_->Setbuffer(BufferMatrix_);
	buffer_->UnMap();
}

void WorldTransform::DeleateParent()
{
}

Vector3 WorldTransform::GetWorldPosition()
{
	return Vector3(matWorld.m[3][0], matWorld.m[3][1], matWorld.m[3][2]);
}
