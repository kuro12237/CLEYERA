#include "CharacterDeadParticle.h"


using namespace Engine;
using namespace Engine::Manager;
using namespace Engine::Transform;


void CharacterDeadParticle::Initialize()
{
    if (initializeLock_)
    {
        return;
    }
    initializeLock_ = true;
    texHandle_ = TextureManager::LoadPngTexture("circle.png");
    uint32_t modelHandle = ModelManager::LoadObjectFile("DfCube");

    name_ = VAR_NAME(CharacterDeadParticle);

    Create(modelHandle);

	block_ = make_unique<Particle::ParticleField<Particle::FieldType::FieldHitBox>>();
	block_->CreateType("Block");
}

void CharacterDeadParticle::Update()
{

   particle_->CallBarrier();
   boxEmitter_->Emit(particle_);
   boxEmitter_->Update();
 

    particle_->CallBarrier();
    block_->Update();
    block_->Dispach(particle_.get());

    particle_->CallBarrier();
    particle_->Update();
}

