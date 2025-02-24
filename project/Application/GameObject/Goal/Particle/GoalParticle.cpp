#include "GoalParticle.h"

using namespace Engine;
using namespace Engine::Manager;
using namespace Engine::Transform;


void GoalParticle::Initialize()
{

   field_ = make_unique<Particle::ParticleField<Particle::FieldType::FieldSuction>>();
   name_ = "GoalParticle";

   texHandle_ = TextureManager::LoadDDSTexture("circle.dds");
  
   name_ = VAR_NAME(GoalParticle);
   this->particle_ = make_unique<Particle::GpuParticle>();
   this->particle_->Create(1, name_);
   this->particle_->SetTexhandle(texHandle_);
   particle_->SetMode(BlendAdd);

   this->emitter_ = make_unique<Particle::ParticleEmitter<Particle::EmitType::Circle>>();
   this->emitter_->CreateType(particle_);


   field_->CreateType(name_ + "Suction");
}

void GoalParticle::ImGuiUpdate()
{
   field_->ImGuiUpdate();
}

void GoalParticle::Update()
{
   particle_->CallBarrier();
   emitter_->Update();
   emitter_->Emit(particle_);
   particle_->CallBarrier();
   field_->Update();
   field_->Dispach(particle_.get());
   particle_->CallBarrier();
   particle_->Update();
}

void GoalParticle::Draw()
{
   particle_->Draw();
   emitter_->SpownDraw();
}
