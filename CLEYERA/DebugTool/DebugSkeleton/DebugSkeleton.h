#pragma once
#include"GraphicsPipelineManager.h"
#include"CreateResource.h"
#include"CameraData.h"
#include"ModelManager.h"
#include"Game3dObject.h"

class DebugSkeleton
{
public:
	DebugSkeleton() {};
	~DebugSkeleton() {};

	void Create(SAnimation::Skeleton skeleton,WorldTransform w);

	void Draw(CameraData camera);

private:

	void CreateJoint(size_t size);

	const SAnimation::Skeleton* skeleton_;
	const WorldTransform* wT_;

	uint32_t jointModelHandle_ = 0;
	Game3dObjectDesc jointObjectDesc_ = {};
	vector<WorldTransform>jointWt_;
	vector<unique_ptr<Game3dObject>>jointObject_;

};