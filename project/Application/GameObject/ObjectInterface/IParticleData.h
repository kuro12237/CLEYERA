#pragma once
#include "Graphics/TextureManager/TextureManager.h"
#include "Particle/Emitter/ParticleEmitter.h"
#include "Particle/GpuParticle.h"

#include "JsonComponent.h"

class ParticleComponent : public JsonComponent
{
 public:
   ParticleComponent() {};
   virtual ~ParticleComponent() {};

   virtual void Initialize() = 0;

   virtual void Update();

   /// <summary>
   /// 描画
   /// </summary>
   void Draw();

   /// <summary>
   /// Emitterのパラメーターを初期化
   /// </summary>
   /// <param name="index"></param>
   void ClearEmitter(uint32_t index) { boxEmitter_->Clear(index); }

   /// <summary>
   /// ImGui更新
   /// </summary>
   void ImGuiUpdate();

#pragma region Get

   Engine::Particle::ParticleEmitter<Engine::Particle::EmitType::BoxParam> *GetBoxEmitter()
   {
      return boxEmitter_.get();
   };

   Engine::Particle::ParticleEmitter<Engine::Particle::EmitType::SphereParam> *GetSphereEmitter()
   {
      return sphereEmitter_.get();
   };
   Engine::Particle::GpuParticle *GetParticle() { return particle_.get(); };
#pragma endregion

 protected:
   /// <summary>
   /// パーティクル作成
   /// </summary>
   void Create(uint32_t modelHandle = 0);

   /// <summary>
   /// データ読み込み
   /// </summary>
   void GetLoadDatas();

   string name_ = "";
   uint32_t texHandle_ = 0;

   unique_ptr<Engine::Particle::GpuParticle> particle_ = nullptr;
   unique_ptr<Engine::Particle::ParticleEmitter<Engine::Particle::EmitType::BoxParam>> boxEmitter_ =
       nullptr;
   unique_ptr<Engine::Particle::ParticleEmitter<Engine::Particle::EmitType::SphereParam>>
       sphereEmitter_ = nullptr;

 private:
   bool isWriteEmitFileParam_ = false;
};