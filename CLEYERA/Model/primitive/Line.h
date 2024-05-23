#pragma once
#include"GraphicsPipelineManager.h"
#include"BufferResources.h"
#include"CameraData.h"
#include"Utility/CameraManager/CameraManager.h"

class LineModel
{
public:
	LineModel() {};
	~LineModel() {};

	void Create();

	void Draw(Math::Vector::Vector3 start, Math::Vector::Vector3  end);

	void SetWorldMat(const Math::Matrix::Matrix4x4 mat) { mat_ = mat; }

private:

	unique_ptr<BufferResource<VertexData>>vertex_;
	unique_ptr<BufferResource<Material>>material_;
	unique_ptr<BufferResource<Math::Matrix::Matrix4x4>>worldMat_;
	Math::Matrix::Matrix4x4 mat_{};
};