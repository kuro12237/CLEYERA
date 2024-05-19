#include "DebugSkeleton.h"

void DebugSkeleton::Create(SAnimation::Skeleton skeleton, WorldTransform w)
{
	wT_ = &w;
	jointSize_ = skeleton.joints.size();

	CreateJoint(jointSize_);
}

void DebugSkeleton::Draw(CameraData camera, SAnimation::Skeleton skeleton)
{
	Math::Matrix::Matrix4x4 sm = Math::Matrix::ScaleMatrix({ jointScale_,jointScale_,jointScale_ });
	for (int i = 0; i < jointSize_; i++)
	{
		jointWt_[i].matWorld = skeleton.joints[i].skeletonSpaceMatrix;
		jointWt_[i].matWorld = Math::Matrix::ScaleMatrixByAnother(jointWt_[i].matWorld,sm);

		jointWt_[i].TransfarMatrix();

		jointObject_->Draw(jointWt_[i], camera);
	}
}

void DebugSkeleton::CreateJoint(size_t size)
{
	jointWt_.resize(size);
	//jointObject_.resize(size);

	jointObjectDesc_.useLight = true;
	jointObjectDesc_.colorDesc.color_ = { 0.0f,1.0f,0.0f };
	jointModelHandle_ = ModelManager::LoadObjectFile("DebugTestBox");
	for (size_t i = 0; i < size; i++)
	{
		jointWt_[i].Initialize();

	}
	jointObject_ = make_unique<Game3dObject>();
	jointObject_->Create(make_unique<Phong3dPipline>());
	jointObject_->SetDesc(jointObjectDesc_);
	jointObject_->SetModel(jointModelHandle_);
}
