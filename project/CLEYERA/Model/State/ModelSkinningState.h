#pragma once
#include"IModelState.h"
#include"Model.h"
#include"ModelManager.h"
#include"Vector/VectorTransform.h"
#include"Light/LightingManager.h"

namespace Engine::Objects
{

	class ModelSkinningState :public IModelState
	{
	public:
		ModelSkinningState() {};
		~ModelSkinningState();

		/// <summary>
		/// èâä˙âª
		/// </summary>
		void Initialize(Model* state)override;

		/// <summary>
		/// ï\é¶
		/// </summary>
		/// <param name="state"></param>
		/// <param name="instancingNum"></param>
		void Draw(Model* state, uint32_t instancingNum)override;

	private:
		unique_ptr<Engine::Buffer::BufferResource<uint32_t>>index_ = nullptr;
		unique_ptr<Engine::Buffer::BufferResource<VertexData>>vertex_ = nullptr;

	};
}