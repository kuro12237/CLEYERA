#pragma once
#include"WorldTransform.h"

namespace Engine::Objects {

	class Model;
	class IModelState
	{
	public:
		virtual ~IModelState() {};
		virtual void Initialize(Model* state) = 0;

		virtual void Draw(Model* state, uint32_t instancingNum) = 0;
	private:

	};
}
