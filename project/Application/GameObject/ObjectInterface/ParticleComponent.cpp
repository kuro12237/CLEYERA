#include "ParticleComponent.h"

using namespace Engine;
using namespace Engine::Manager;
using namespace Engine::Transform;

void ParticleComponent::Update()
{
   particle_->CallBarrier();
   particle_->Update();
}

void ParticleComponent::Draw()
{
   boxEmitter_->SpownDraw();
   particle_->Draw();
}

void ParticleComponent::Create(uint32_t modelHandle)
{
   particle_ = make_unique<Particle::GpuParticle>();
   particle_->Create(1, name_, modelHandle);

   boxEmitter_ = make_unique<Particle::ParticleEmitter<Particle::EmitType::BoxParam>>();
   boxEmitter_->CreateType(particle_);

   sphereEmitter_ = make_unique<Particle::ParticleEmitter<Particle::EmitType::SphereParam>>();
   sphereEmitter_->CreateType(particle_);

   jsonGropName_ = boxEmitter_->GetEmitName();
   CreateJsonData();

   for (size_t i = 0; i < boxEmitter_->GetEmitMax(); i++) {
      string name = "emitParam" + to_string(i);

      this->AddJsonItem(name.c_str(), boxEmitter_->GetEmitParam()[i]);
      boxEmitter_->GetEmitParam()[i] = GetJsonItem<Particle::EmitType::BoxParam>(name);
   }
}

void ParticleComponent::GetLoadDatas()
{
   for (size_t i = 0; i < boxEmitter_->GetEmitMax(); i++) {
      string name = "emitParam" + to_string(i);
      boxEmitter_->GetEmitParam()[i] = GetJsonItem<Particle::EmitType::BoxParam>(name);
   }
}

void ParticleComponent::ImGuiUpdate()
{
   string name = boxEmitter_->GetEmitName() + "writeParam";
   ImGui::Checkbox(name.c_str(), &isWriteEmitFileParam_);
   if (isWriteEmitFileParam_) {
      for (size_t i = 0; i < boxEmitter_->GetEmitMax(); i++) {
         string name = "emitParam" + to_string(i);
         boxEmitter_->GetEmitParam()[i] = GetJsonItem<Particle::EmitType::BoxParam>(name);
      }
   }

   boxEmitter_->ImGuiUpdate();
}
