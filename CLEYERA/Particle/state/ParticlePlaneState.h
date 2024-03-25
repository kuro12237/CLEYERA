#pragma once
#include"IParticleState.h"
#include"CreateResource.h"

#include"GraphicsPipelineManager.h"
#include"Particle/Particle.h"
#include"Graphics/TextureManager/TextureManager.h"
#include"Model.h"


class ParticlePlaneState: public IParticleState
{
public:
	ParticlePlaneState() {};
	~ParticlePlaneState() {};

	void Initialize(Particle* state)override;

	void Draw(Particle* state, list<Particle_param>param, CameraData  viewprojection)override;

private:

	SPSOProperty Get3dParticlePipeline(Particle* state);

	void CarmeraBillbord(CameraData  view);

	void CommandCall(uint32_t TexHandle, Particle* state, CameraData  view);
	
	uint32_t NumInstansing = 0;
	uint32_t NumDrawInstansing = 0;
	bool NumInstansingLock = false;

	uint32_t dsvIndex = 0;

	Vector4 testColor = { 1,1,1,1 };

	Vector4 pos = { 0,0,0,1 };
	float size = 0.5f;

	const uint32_t VertexSize = 4;
	const uint32_t IndexSize = 6;
	ResourcePeroperty resource_ = {};
	

	Matrix4x4 billboardMatrix{};

	Matrix4x4 sMat{};
	Matrix4x4 tMat{};
	
};



