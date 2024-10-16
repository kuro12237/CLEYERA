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

		void Initialize(Model* state)override;
		void Draw(Model* state, uint32_t instancingNum)override;

	private:
		unique_ptr<Engine::Buffer::BufferResource<uint32_t>>index_ = nullptr;
		unique_ptr<Engine::Buffer::BufferResource<VertexData>>vertex_ = nullptr;

	};
}