#include "PlayerCamera.h"

using namespace Engine::Transform;


void PlayerCamera::Initialize()
{
	name_ = "PlayerCamera";
	
	objectData_ = gameObjectManager_->GetCameraData(name_);
	auto transform = objectData_.lock()->GetWorldTransform().transform;
	transform.scale = { 1.0f,1.0f,1.0f };
	transform.rotate.x = 0.1f;
}

void PlayerCamera::Update()
{
	auto& cameraWt = objectData_.lock()->GetWorldTransform();

	if (target_)
	{
		interTarget_ = Math::Vector::Lerp(interTarget_, target_->transform.translate, 0.25f);
	}

	Math::Vector::Vector3 offset ={ 0.0f,0.0f,-64.0f };
	offset = CalcOffset(cameraWt, offset);
	cameraWt.transform.translate = Math::Vector::Add(interTarget_, offset);
}

void PlayerCamera::Shake()
{
	
}

Math::Vector::Vector3 PlayerCamera::CalcOffset(const WorldTransform& w, const Math::Vector::Vector3 v) const
{
	Math::Matrix::Matrix4x4 rotateMatrix = Math::Matrix::RotateXYZMatrix(
		w.transform.rotate.x, w.transform.rotate.y, w.transform.rotate.z);

	Math::Vector::Vector3 offset = v;
	offset = Math::Vector::TransformNormal(offset, rotateMatrix);
	return offset;
}
