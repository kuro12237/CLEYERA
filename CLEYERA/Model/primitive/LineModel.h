#pragma once
#include"GraphicsPipelineManager.h"
#include"BufferResources.h"
#include"CameraData.h"
#include"Utility/CameraManager/CameraManager.h"
#include"Primitive.h"


namespace Primitive {

	class LineModel
	{
	public:
		LineModel() {};
		~LineModel() {};

		void Create(string name, uint32_t vertexNum = 2);
		void Draw();

#pragma region Set

		void SetMaterial(Material material) { color_ = material; }
		void SetWorldMat(const Math::Matrix::Matrix4x4 mat) { mat_ = mat; }

#pragma endregion

		void Clear() { lines_.clear(); }
		void PushBack(const Math::Vector::Vector3 s, const Math::Vector::Vector3 e, size_t index) { lines_.push_back(s), lines_.push_back(e); index; }

	private:

		void CommandCall();

		unique_ptr < BufferResource < Math::Vector::Vector3 >> verticesBuf_;
		vector<Math::Vector::Vector3>lines_;

		unique_ptr<BufferResource<VertexData>>vertex_;
		unique_ptr<BufferResource<Material>>material_;
		Material color_ = {};
		unique_ptr<BufferResource<Math::Matrix::Matrix4x4>>worldMat_;
		Math::Matrix::Matrix4x4 mat_{};
	};
}