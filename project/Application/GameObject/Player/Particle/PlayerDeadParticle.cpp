#include "PlayerDeadParticle.h"

using namespace Engine;
using namespace Engine::Manager;
using namespace Engine::Transform;

void PlayerDeadParticle::Initialize()
{

   name_ = VAR_NAME(PlayerDeadParticle);
   this->Create();

   texHandle_ = Engine::Manager::TextureManager::LoadPngTexture("deadEffect.png");
   particle_->SetTexhandle(texHandle_);

}

void PlayerDeadParticle::Update()
{
   if (isEmit_) {

      auto &emit = boxEmitter_->GetEmitParam()[0];
      auto &control = boxEmitter_->GetControlParam()[0];

      control.useFlag_ = true;
      control.frequencyTime = 0.5f;
      emit.count = 3;

      emit.velocityMax = {0.1f, 0.1f, 0.1f};
      emit.velocityMin = {-0.1f, -0.1f, -0.1f};
      emit.translate = *p_PlayerPos_;
   }

 
   boxEmitter_->Emit(particle_);
   boxEmitter_->Update();
   particle_->CallBarrier();
   particle_->Update();
}
