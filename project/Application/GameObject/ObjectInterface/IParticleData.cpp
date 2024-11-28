#include "IParticleData.h"


using namespace Engine;
using namespace Engine::Manager;
using namespace Engine::Transform;

void IParticleData::Update()
{
	particle_->CallBarrier();
	particle_->Update();
}

void IParticleData::Draw()
{
	particle_->Draw();
}

void IParticleData::Create()
{
	particle_ = make_unique<Particle::GpuParticle>();
	particle_->Create(1, name_);

	emitter_ = make_unique<Particle::ParticleEmitter<Particle::EmitType::BoxParam>>();
	emitter_->CreateType(particle_);

	jsonGropName_ = emitter_->GetEmitName();
	CreateJsonData();
}

void IParticleData::CreateParamJson()
{
	for (size_t i = 0; i < emitter_->GetEmitMax(); i++)
	{

	}

}

void IParticleData::UpdateParamJson()
{
	for (size_t i = 0; i < emitter_->GetEmitMax(); i++)
	{

	}
}

void IParticleData::ImGuiUpdate()
{
	emitter_->ImGuiUpdate();
}
