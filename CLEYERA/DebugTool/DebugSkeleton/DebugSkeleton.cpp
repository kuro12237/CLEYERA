#include "DebugSkeleton.h"

void DebugSkeleton::Create(SAnimation::Skeleton skeleton, WorldTransform w)
{
	wT_ = &w;
	jointSize_ = skeleton.joints.size();

	CreateJoint(jointSize_);
}

void DebugSkeleton::Draw(CameraData camera, SAnimation::Skeleton skeleton)
{
	for (int i = 0; i < jointSize_; i++)
	{
		jointWt_[i].matWorld = skeleton.joints[i].skeletonSpaceMatrix;

		jointWt_[i].matWorld = Math::Matrix::ScaleMatrixByAnother(jointWt_[i].matWorld, Math::Matrix::ScaleMatrix({ 20,20,20 }));

		jointWt_[i].TransfarMatrix();

		jointObject_[i]->Draw(jointWt_[i], camera);
	}
}

void DebugSkeleton::CreateJoint(size_t size)
{
	jointWt_.resize(size);
	jointObject_.resize(size);

	jointObjectDesc_.useLight = true;
	jointModelHandle_ = ModelManager::LoadObjectFile("DebugTestBox");
	for (size_t i = 0; i < size; i++)
	{
		jointWt_[i].Initialize();
		jointObject_[i] = make_unique<Game3dObject>();
		jointObject_[i]->Create(make_unique<Phong3dPipline>());
		jointObject_[i]->SetDesc(jointObjectDesc_);
		jointObject_[i]->SetModel(jointModelHandle_);
	}

}
