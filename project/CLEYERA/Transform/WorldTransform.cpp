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
	if (!parent)
	{
		return;
	}

	Math::Matrix::Matrix4x4 mat = matWorld;
	transform.translate = GetWorldPosition();
	transform.scale = GetWorldScale();
	transform.rotate = GetWorldRotate();

	parent = nullptr;
	matWorld = matWorld;
}

Vector3 WorldTransform::GetWorldPosition()
{
	return Vector3(matWorld.m[3][0], matWorld.m[3][1], matWorld.m[3][2]);
}

Math::Vector::Vector3 Engine::Transform::WorldTransform::GetWorldRotate()
{

	Vector3 scale = GetWorldScale();
	Math::Matrix::Matrix4x4 rotationMatrix = matWorld;

	rotationMatrix.m[0][0] /= scale.x;
	rotationMatrix.m[0][1] /= scale.x;
	rotationMatrix.m[0][2] /= scale.x;

	rotationMatrix.m[1][0] /= scale.y;
	rotationMatrix.m[1][1] /= scale.y;
	rotationMatrix.m[1][2] /= scale.y;

	rotationMatrix.m[2][0] /= scale.z;
	rotationMatrix.m[2][1] /= scale.z;
	rotationMatrix.m[2][2] /= scale.z;

	float pitch = asinf(-rotationMatrix.m[2][1]);
	float yaw = atan2f(rotationMatrix.m[2][0], rotationMatrix.m[2][2]);
	float roll = atan2f(rotationMatrix.m[0][1], rotationMatrix.m[1][1]);

	return Vector3(pitch, yaw, roll);
}

Math::Vector::Vector3 Engine::Transform::WorldTransform::GetWorldScale()
{
	return Vector3(
		sqrtf(matWorld.m[0][0] * matWorld.m[0][0] +
			matWorld.m[0][1] * matWorld.m[0][1] +
			matWorld.m[0][2] * matWorld.m[0][2]),
		sqrtf(matWorld.m[1][0] * matWorld.m[1][0] +
			matWorld.m[1][1] * matWorld.m[1][1] +
			matWorld.m[1][2] * matWorld.m[1][2]),
		sqrtf(matWorld.m[2][0] * matWorld.m[2][0] +
			matWorld.m[2][1] * matWorld.m[2][1] +
			matWorld.m[2][2] * matWorld.m[2][2])
	);
}
