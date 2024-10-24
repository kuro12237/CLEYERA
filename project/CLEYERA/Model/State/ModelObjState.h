#pragma once
#include"IModelState.h"
#include"Model.h"
#include"ModelManager.h"
#include"Vector/VectorTransform.h"
#include"Light/LightingManager.h"

namespace Engine::Objects {

	using namespace Engine::Buffer;

	class ModelObjState :public IModelState
	{
	public:
		ModelObjState() {};
		~ModelObjState();

		/// <summary>
		/// èâä˙âª
		/// </summary>
		void Initialize(Model* state)override;

		/// <summary>
		/// ï\é¶
		/// </summary>
		void Draw(Model* state, uint32_t instancingNum)override;

	private:
		unique_ptr<BufferResource<uint32_t>>index_ = nullptr;
		unique_ptr<BufferResource<VertexData>>vertex_ = nullptr;
	};
}