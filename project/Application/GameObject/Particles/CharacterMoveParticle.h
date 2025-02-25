#pragma once
#include "GameObject/ObjectInterface/ParticleComponent.h"
#include "Graphics/TextureManager/TextureManager.h"
#include "Particle/Emitter/ParticleEmitter.h"
#include "Particle/GpuParticle.h"

/// <summary>
/// キャラクターの動く時のパーティクル
/// </summary>
class CharacterMoveParticle : public ParticleComponent
{
 public:
   CharacterMoveParticle() {};
   ~CharacterMoveParticle() {};

   /// <summary>
   /// 初期化
   /// </summary>
   void Initialize();

   /// <summary>
   /// 更新
   /// </summary>
   void Update();

   /// <summary>
   /// 描画
   /// </summary>
   void Draw();

   /// <summary>
   /// ImGui更新
   /// </summary>
   void ImGuiUpdate();

   /// <summary>
   /// Emitterのパラメーターを初期化
   /// </summary>
   /// <param name="index"></param>
   void ClearEmitter(uint32_t index) { emitter_->Clear(index); }

   /// <summary>
   /// パーティクルを沸かせる
   /// </summary>
   void Emit();

#pragma region Get
   Engine::Particle::ParticleEmitter<Engine::Particle::EmitType::BoxParam> *GetEmitter()
   {
      return emitter_.get();
   };
#pragma endregion

 private:
   bool InitializeLock_ = false;
   string name_ = "CharacterMoveParticle";
   uint32_t texHandle_ = 0;

   unique_ptr<Engine::Particle::GpuParticle> particle_ = nullptr;
   unique_ptr<Engine::Particle::ParticleEmitter<Engine::Particle::EmitType::BoxParam>> emitter_ =
       nullptr;

};
