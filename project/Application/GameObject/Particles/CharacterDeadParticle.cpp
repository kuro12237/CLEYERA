#include "CharacterDeadParticle.h"


using namespace Engine;
using namespace Engine::Manager;
using namespace Engine::Transform;

CharacterDeadParticle* CharacterDeadParticle::GetInstance()
{
    static CharacterDeadParticle instance;
    return &instance;
}

void CharacterDeadParticle::Initialize()
{
    if (initializeLock_)
    {
        return;
    }
    initializeLock_ = true;
    texHandle_ = TextureManager::LoadPngTexture("circle.png");
    uint32_t modelHandle = ModelManager::LoadObjectFile("DfCube");

    particle_ = make_unique<Particle::GpuParticle>();
    particle_->Create(1,name_,modelHandle);

    emitter_ = make_unique<Particle::ParticleEmitter<Particle::EmitType::BoxParam>>();
    emitter_->CreateType(particle_);

	block_ = make_unique<Particle::ParticleField<Particle::FieldType::FieldHitBox>>();
	block_->CreateType("Block");
}

void CharacterDeadParticle::Update()
{
    particle_->CallBarrier();
    emitter_->Update();
    emitter_->Emit(particle_);

    particle_->CallBarrier();
    block_->Update();
    block_->Dispach(particle_.get());

    particle_->CallBarrier();
    particle_->Update();
}

void CharacterDeadParticle::Draw()
{
    particle_->Draw();
    emitter_->SpownDraw();
}

void CharacterDeadParticle::ImGuiUpdate()
{

    block_->ImGuiUpdate();
    emitter_->ImGuiUpdate();
}
