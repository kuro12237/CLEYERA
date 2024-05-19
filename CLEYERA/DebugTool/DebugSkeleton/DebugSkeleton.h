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

	void Draw(CameraData camera, SAnimation::Skeleton skeleton);

	void ImGuiUpdate();

private:

	void CreateJoint(size_t size);

	const WorldTransform* wT_;
	
	size_t jointSize_ = 0;

	float jointScale_ = 16.0f;

	uint32_t jointModelHandle_ = 0;
	Game3dObjectDesc jointObjectDesc_ = {};
	vector<WorldTransform>jointWt_;
	unique_ptr<Game3dObject>jointObject_;

};