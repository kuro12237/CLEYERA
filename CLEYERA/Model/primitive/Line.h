#pragma once
#include"GraphicsPipelineManager.h"
#include"BufferResources.h"
#include"CameraData.h"
#include"Utility/CameraManager/CameraManager.h"
#include"Primitive.h"

class LineModel
{
public:
	LineModel() {};
	~LineModel() {};

	void Create(string name, uint32_t vertexNum = 2 );
	void Draw();

	void SetMaterial(Material material) { color_ = material; }
	void SetWorldMat(const Math::Matrix::Matrix4x4 mat) { mat_ = mat; }
	void SetStartEndPos(const Math::Vector::Vector3 s, const Math::Vector::Vector3 e) { start = s, end = e; }
	void Clear() { lines_.clear(); }
	void PushBack(const Math::Vector::Vector3 s, const Math::Vector::Vector3 e, size_t index) { lines_.push_back(s), lines_.push_back(e); index; }

private:

	const uint32_t verticesMax_ = 640;
	unique_ptr < BufferResource < Math::Vector::Vector3 >> verticesBuf_;
	vector<Math::Vector::Vector3>lines_;

	unique_ptr<BufferResource<VertexData>>vertex_;
	unique_ptr<BufferResource<Material>>material_;
	Material color_ = {};
	unique_ptr<BufferResource<Math::Matrix::Matrix4x4>>worldMat_;
	Math::Matrix::Matrix4x4 mat_{};
	Math::Vector::Vector3 start = {};
	Math::Vector::Vector3  end = {};
};