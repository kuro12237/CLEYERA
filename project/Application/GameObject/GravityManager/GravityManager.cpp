#include "GravityManager.h"

void GravityManager::Initialize()
{
	particleGravityField_= make_unique<Engine::Particle::ParticleField<Engine::Particle::FieldType::FieldGravity>>();
	particleGravityField_->CreateType("GameSceneParticleGravity");

	auto& param = particleGravityField_->GetParam(0);

	const float kscale = 256.0f;
	param.sizeMax = {kscale,kscale,kscale};
	param.sizeMin = { -kscale,-kscale,-kscale };
	param.use = 1;
	param.gravity = -0.01f;
}

void GravityManager::Update()
{
	particleGravityField_->ImGuiUpdate();
	particleGravityField_->Update();
}

void GravityManager::CheckGravity()
{
	list<ObjectComponent*>::iterator itrA = objectDatas_.begin();

	for (; itrA != objectDatas_.end(); ++itrA) {

		ObjectComponent* objA = *itrA;
		objA->CalcGravity(-gravity_);
	}

	//particle
	if (particleGravityField_)
	{
		for (auto& p : particles_)
		{
			p->CallBarrier();
			particleGravityField_->Dispach(p);
		}
	}

}
