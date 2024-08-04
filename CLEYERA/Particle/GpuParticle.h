#pragma once
#include"Graphics/DescripterManager/DescriptorManager.h"
#include"BufferResources.h"
#include"CreateResource.h"
#include"WorldTransform.h"
#include"Graphics/PipelineManager/GraphicsPipelineManager.h"
#include"Utility/CameraManager/CameraManager.h"
#include"Utility/RuntimeCounter/RunTimeCounter.h"

struct ParticleCS
{
	Math::Vector::Vector3 translate;
	Math::Vector::Vector3 scale;
	Math::Vector::Vector3 rotate;
	Math::Matrix::Matrix4x4 matWorld;
	float lifeTime;
	Math::Vector::Vector3 velocity;
	float currentTime;
	Math::Vector::Vector4 color = {1.0f,1.0f,1.0f,1.0f};
	bool isDraw_ = false;
};

namespace Particle {

	class GpuParticle
	{
	public:
		GpuParticle() {};
		~GpuParticle() {};

		void Create(const size_t num, string Name);

		void Update();

		void Draw();

		void CallBarrier();

		void CallUavRootparam(uint32_t rootParamIndex);

#pragma region Set

		void SetTexhandle(uint32_t texHandle) { texHandle_ = texHandle; }

#pragma endregion

#pragma region Get

		string GetName() { return name_; }
		uint32_t GetNum() { return uint32_t(particleNum_); }
		BufferResource<uint32_t>*GetfreeCountBuf() { return freeCounterBuf_.get(); }

#pragma endregion


	private:

		size_t particleNum_ = 0;
		string name_ = "";

		const int vertexNum = 4;
		const int indexNum = 6;
		unique_ptr<BufferResource<VertexData>>vertexBuf_ = nullptr;
		vector<VertexData>vertexParam_;
		unique_ptr<BufferResource<uint32_t>>indexBuf_ = nullptr;
		vector<uint32_t>indexParam_;

		unique_ptr<BufferResource<ParticleCS>>writeParticleBuf_ = nullptr;
		vector<ParticleCS>writeParticleParam_;

		unique_ptr<BufferResource<uint32_t>>freeCounterBuf_ = nullptr;
		vector<uint32_t>freeCounter_;

		uint32_t texHandle_ = 1;
	};

};