#include "TitleNameParticle.h"

void TitleNameParticle::Initialize()
{
	this->name_ = "TitleNameParticle";

	
	this->Create();
	this->particle_->SetDrawMode(Engine::Particle::DrawMode::mode_2d);
	uint32_t texHandle = Engine::Manager::TextureManager::LoadDDSTexture("circle.dds");
	this->particle_->SetTexhandle(texHandle);
	this->particle_->Set2dSize(Engine::Manager::TextureManager::GetTextureSize(texHandle));
	this->particle_->SetMode(SpriteMode::BlendAdd);

	Math::Vector::Vector2 pos = Engine::Manager::TextureManager::GetTextureSize(texHandle);
	pos.x *= -0.5f;
	pos.y *= -0.5f;
	this->particle_->SetPos(pos);
	auto& control = boxEmitter_->GetControlParam();
	control[0].useFlag_ = true;
	control[1].useFlag_ = true;

	this->GetLoadDatas();
}

void TitleNameParticle::Update()
{
	boxEmitter_->Update();
	boxEmitter_->Emit(particle_);
	particle_->CallBarrier();
	particle_->Update();
}
