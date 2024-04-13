#include "WorldTransform.h"

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
	scale = s;
	rotation = r;
	translate = t;
	UpdateMatrix();
}

void WorldTransform::UpdateMatrix()
{
	matWorld = Math::Matrix::AffineMatrix(scale, rotation, translate);

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
