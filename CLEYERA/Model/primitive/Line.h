#pragma once
#include"GraphicsPipelineManager.h"
#include"BufferResources.h"
#include"CameraData.h"

class LineModel
{
public:
	LineModel() {};
	~LineModel() {};

	void Create();

	void Draw(Math::Matrix::Matrix4x4 startMat,Math::Matrix::Matrix4x4 endMat,const CameraData& camera);

private:

	unique_ptr<BufferResource<VertexData>>vertex_;
	unique_ptr<BufferResource<Material>>material_;
};