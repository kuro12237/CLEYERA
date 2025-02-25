#pragma once
#include "GameObject/ObjectInterface/ParticleComponent.h"
#include "Graphics/TextureManager/TextureManager.h"
#include "Particle/Emitter/ParticleEmitter.h"
#include "Particle/Field/ParticleField.h"
#include "Particle/GpuParticle.h"

/// <summary>
/// キャラクターが死んだときのパーティクル
/// </summary>
class CharacterDeadParticle : public ParticleComponent
{
 public:
   CharacterDeadParticle() {};
   ~CharacterDeadParticle() {};
   /// <summary>
   /// 初期化
   /// </summary>
   void Initialize() override;

   /// <summary>
   /// 更新
   /// </summary>
   void Update() override;

#pragma region Get
#pragma endregion

 private:
   bool initializeLock_ = false;
   string name_ = "CharacterDeadParticle";
   uint32_t texHandle_ = 0;

   unique_ptr<Engine::Particle::ParticleField<Engine::Particle::FieldType::FieldHitBox>> block_ =
       nullptr;
};
