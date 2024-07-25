#pragma once
#include"Graphics/DescripterManager/DescriptorManager.h"
#include"BufferResources.h"
#include"CreateResource.h"
#include"WorldTransform.h"
#include"Graphics/PipelineManager/GraphicsPipelineManager.h"

struct ParticleCS
{
	Math::Vector::Vector3 translate;
	Math::Vector::Vector3 scale;
	float lifeTime;
	Math::Vector::Vector3 velocity;
	float currentTime;
	Math::Vector::Vector4 color = {1.0f,1.0f,1.0f,1.0f};
};

class GpuParticle
{
public:
	GpuParticle() {};
	~GpuParticle() {};

	void Create(const size_t num,string Name);

	void Update();

	void Draw();

private:

	size_t particleNum_ = 0;
	string name_ = "";

	const int vertexNum = 4;
	const int indexNum = 6;
	unique_ptr<BufferResource<VertexData>>vertexBuf_ = nullptr;
	vector<VertexData>vertexParam_;
	unique_ptr<BufferResource<uint32_t>>indexBuf_ = nullptr;
	vector<uint32_t>indexParam_;

	unique_ptr<BufferResource<ParticleCS>>particleBuf_ = nullptr;
	vector<ParticleCS>particleParam_;

	uint32_t texHandle_ = 0;


};

