#pragma once
#include"Game3dObject.h"
#include"WorldTransform.h"

#include"Game3dInstancingObject/GameInstancing3dObject.h"
#include"Transform/STransformEular.h"

#include"Utility/ObjectManager/Game3dInstancingObjectData.h"
#include"Utility/ObjectManager/GameCameraData.h"
#include"Utility/ObjectManager/Game3dObjectData.h"

#include"Particle/GpuParticle.h"
#include"Particle/Emitter/ParticleEmitter.h"

/// <summary>
/// 読み込んだオブジェクトを格納
/// </summary>
struct LevelData
{
	uint32_t objectNum = 0;
	std::map<string,shared_ptr<Game3dObjectData>> obj3dData;
	std::map<string,shared_ptr<Game3dInstancingObjectData>>objInstancing3dData;
	std::map<string, shared_ptr<GameCameraData>>cameraData;

	std::map<string, shared_ptr<Engine::Particle::GpuParticle>>particles;
	std::map<string, shared_ptr<Engine::Particle::ParticleEmitter<Engine::Particle::EmitType::BoxParam>>>particlesEmitter_;
};
