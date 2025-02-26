#include "PlayerCamera.h"

using namespace Engine::Transform;

void PlayerCamera::Initialize()
{
   name_ = VAR_NAME(PlayerCamera);

   objectData_ = gameObjectManager_->GetCameraData(name_);
   auto transform = objectData_.lock()->GetWorldTransform().transform;
   
   this->jsonGropName_ = name_;
   CreateJsonData();

   AddJsonItem<decltype(cameraRotateX_)>(VAR_NAME(cameraRotateX_), cameraRotateX_);
   cameraRotateX_ = GetJsonItem<decltype(cameraRotateX_)>(VAR_NAME(cameraRotateX_));
   transform.rotate.x = cameraRotateX_;

   AddJsonItem<decltype(cameraFacter_)>(VAR_NAME(cameraFacter_), cameraFacter_);
   cameraFacter_ = GetJsonItem<decltype(cameraFacter_)>(VAR_NAME(cameraFacter_));

   AddJsonItem<decltype(cameraOffset_)>(VAR_NAME(cameraOffset_), cameraOffset_);
   cameraOffset_ = GetJsonItem<decltype(cameraOffset_)>(VAR_NAME(cameraOffset_));
}

void PlayerCamera::Update()
{
   auto &cameraWt = objectData_.lock()->GetWorldTransform();

   if (target_) {
      interTarget_ = Math::Vector::Lerp(interTarget_, target_->transform.translate, cameraFacter_);
   }

   Math::Vector::Vector3 offset = cameraOffset_;
   offset = CalcOffset(cameraWt, offset);
   cameraWt.transform.translate = Math::Vector::Add(interTarget_, offset);
}

void PlayerCamera::Shake() {}

Math::Vector::Vector3 PlayerCamera::CalcOffset(const WorldTransform &w,
                                               const Math::Vector::Vector3 v) const
{
   Math::Matrix::Matrix4x4 rotateMatrix = Math::Matrix::RotateXYZMatrix(
       w.transform.rotate.x, w.transform.rotate.y, w.transform.rotate.z);

   Math::Vector::Vector3 offset = v;
   offset = Math::Vector::TransformNormal(offset, rotateMatrix);
   return offset;
}
