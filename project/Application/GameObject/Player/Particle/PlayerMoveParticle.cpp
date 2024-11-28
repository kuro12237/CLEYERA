#include "PlayerMoveParticle.h"

void PlayerMoveParticle::Initialize()
{
	name_ = "PlayerMoveParticle";
	this->Create();

	texHandle_ = Engine::Manager::TextureManager::LoadDDSTexture("GameObject/cloud/cloud.dds");
	particle_->SetTexhandle(texHandle_);

	this->CreateParamJson();
}

void PlayerMoveParticle::Update()
{
	this->UpdateParamJson();

	auto &param = emitter_->GetEmitParam()[0];
	if (isEmit_)
	{
		param.count = 1;
	}
	else
	{
		param.count = 0;
	}

	emitter_->Emit(particle_);
	emitter_->Update();
	particle_->CallBarrier();
	particle_->Update();
}
