#include "DebugSkeleton.h"

void DebugSkeleton::Create(SAnimation::Skeleton skeleton, WorldTransform w)
{
	skeleton_ = &skeleton;
	wT_ = &w;

	const size_t jointCount = skeleton_->joints.size();




}

void DebugSkeleton::Draw(CameraData camera)
{


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
