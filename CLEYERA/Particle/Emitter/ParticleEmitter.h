#pragma once
#include"DirectXCommon.h"
#include"IEmitterState.h"
#include"../GpuParticle.h"
#include"StructGpuParticleEmitter.h"
#include"EmitterSphere.h"

namespace Particle {

	class ParticleEmitter
	{
	public:
		ParticleEmitter() {};
		~ParticleEmitter() {};

		void CreateType(unique_ptr<IEmitterState>state, unique_ptr<Particle::GpuParticle>& particle);

		void Update();

		void Emit(unique_ptr<Particle::GpuParticle>& particle);

		void SpownDraw();

#pragma region Get

		vector<SEmitterSphere>& GetSphereParam() { return sphere_; }
		string GetEmitName() { return emitName_; }
		const uint32_t GetEmitMax() { return emitMax_; }
#pragma endregion

	private:

		string emitName_ = "";
		static const uint32_t emitMax_ = 1024;
		uint32_t srvHandle_ = 0;

		unique_ptr<IEmitterState>type_ = nullptr;
		vector<SEmitterSphere>sphere_ = {};

		WorldTransform worldTransform_ = {};

	};
}