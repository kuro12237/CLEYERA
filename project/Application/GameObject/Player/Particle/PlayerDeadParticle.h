#pragma once
#include "Graphics/TextureManager/TextureManager.h"
#include "Particle/Emitter/ParticleEmitter.h"
#include "Particle/GpuParticle.h"

#include "GameObject/ObjectInterface/ParticleComponent.h"

/// <summary>
/// プレイヤーが死んだときのパーティクル
/// </summary>
class PlayerDeadParticle : public ParticleComponent
{
 public:
   PlayerDeadParticle() {};
   ~PlayerDeadParticle() {};
   /// <summary>
   /// 初期化
   /// </summary>
   void Initialize() override;

   /// <summary>
   /// 更新
   /// </summary>
   void Update() override;

   /// <summary>
   /// 描画
   /// </summary>
   void Draw();

   /// <summary>
   /// ImGui更新
   /// </summary>
   void ImGuiUpdate();


#pragma region Get
#pragma endregion

#pragma region Set

   void SetIsEmit(bool f) { isEmit_ = f; }
   void SetPlayerPos(const Math::Vector::Vector3 &p) { p_PlayerPos_ = &p; }
#pragma endregion

 private:
   string name_ = "PlayerDeadParticle";
   uint32_t texHandle_ = 0;

   const Math::Vector::Vector3 *p_PlayerPos_ = nullptr;
   bool isEmit_ = false;
};
