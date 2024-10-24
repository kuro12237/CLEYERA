#pragma once
#include"GraphicsPipelineManager.h"
#include"BufferResources.h"
#include"CameraData.h"
#include"Utility/CameraManager/CameraManager.h"
#include"Primitive.h"


namespace Primitive {

	/// <summary>
	/// ���\���N���X
	/// </summary>
	class LineModel
	{
	public:
		LineModel() {};
		~LineModel() {};

		/// <summary>
		/// buffer�쐬
		/// </summary>
		/// <param name="���O"></param>
		/// <param name="���_��"></param>
		void Create(string name, uint32_t vertexNum = 2);

		/// <summary>
		/// �\��
		/// </summary>
		void Draw();

#pragma region Set
		void SetMaterial(Material material) { color_ = material; }
		void SetWorldMat(const Math::Matrix::Matrix4x4 mat) { mat_ = mat; }
#pragma endregion

		/// <summary>
		/// �p�����[�^�폜
		/// </summary>
		void Clear() { lines_.clear(); }

		/// <summary>
		/// �z��̐��̒���
		/// </summary>
		/// <param name="size"></param>
		void resize(size_t size) { lines_.resize(size); }

		/// <summary>
		/// listpushback
		/// </summary>
		/// <param name="start"></param>
		/// <param name="end"></param>
		/// <param name="�z��ԍ�"></param>
		void PushBack(const Math::Vector::Vector3 s, const Math::Vector::Vector3 e, size_t index = 0) { lines_.push_back(s), lines_.push_back(e); index; }
		
		/// <summary>
		/// �z��ɑ��
		/// </summary>
		/// <param name="s"></param>
		/// <param name="e"></param>
		/// <param name="index"></param>
		void SetVec(const Math::Vector::Vector3 s, const Math::Vector::Vector3 e, size_t index = 0) { lines_[index] = s, lines_[index + 1] = e; index; }

	private:

		void CommandCall();

		unique_ptr < Engine::Buffer::BufferResource < Math::Vector::Vector3 >> verticesBuf_ = nullptr;
		vector<Math::Vector::Vector3>lines_;

		unique_ptr<Engine::Buffer::BufferResource<VertexData>>vertex_ = nullptr;
		unique_ptr<Engine::Buffer::BufferResource<Material>>material_ = nullptr;
		Material color_ = {};
		unique_ptr<Engine::Buffer::BufferResource<Math::Matrix::Matrix4x4>>worldMat_ = nullptr;
		Math::Matrix::Matrix4x4 mat_ = {};
	};
}