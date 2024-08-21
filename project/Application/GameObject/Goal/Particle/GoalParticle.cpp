#include "GoalParticle.h"

GoalParticle* GoalParticle::GetInstance()
{
	static GoalParticle instance;
	return &instance;
}

void GoalParticle::Initialize()
{
	if (InitializeLock_)
	{
		return;
	}
	InitializeLock_ = true;

	particle_ = make_unique<Particle::GpuParticle>();
	emitter_ = make_unique<Particle::ParticleEmitter<Particle::EmitType::Circle>>();
	field_ = make_unique<Particle::ParticleField<Particle::FieldType::FieldSuction>>();
	name_ = "GoalParticle";
	particle_->Create(1, name_);

	texHandle_ = TextureManager::LoadPngTexture("circle.png");
	particle_->SetTexhandle(texHandle_);

	emitter_->CreateType(particle_);
	field_->CreateType(name_ + "Suction");

	//emit
	float kParticleRadious = 2.0f;
	uint32_t kSpownMax = 4;
	float kParticleFrequencyTime = 0.1f;
	float kParticleScale = 0.25f;
	float kColorDecay = 0.02f;
	Math::Vector::Vector4 kColor = ColorConverter::ColorConversion(0xffff00ff);

	auto& emitter = GoalParticle::GetInstance()->GetEmitters()->GetEmitParam()[0];
	auto& control = GoalParticle::GetInstance()->GetEmitters()->GetControlParam()[0];
	control.useFlag_ = true;
	control.frequencyTime = kParticleFrequencyTime;
	emitter.count = kSpownMax;
	emitter.radious = kParticleRadious;
	emitter.scaleSizeMin = { kParticleScale, kParticleScale, kParticleScale };
	emitter.scaleSizeMax = { kParticleScale,kParticleScale,kParticleScale };
	emitter.colorDecayMax = { 0.0f,0.0f,0.0f,kColorDecay };
	emitter.colorDecayMin = { 0.0f,0.0f,0.0f,kColorDecay };
	emitter.color = kColor;

	//fieldParticle
	const float kSize = 8.0f;
	float power = 0.05f;
	auto& fieldParam = field_->GetParam(0);
	fieldParam.use = 1;
	fieldParam.sizeMax = { kSize,kSize,kSize };
	fieldParam.sizeMin = { -kSize,-kSize,-kSize };
	fieldParam.suctionPower = power;
}

void GoalParticle::ImGuiUpdate()
{
	emitter_->ImGuiUpdate();
	field_->ImGuiUpdate();
}

void GoalParticle::Update()
{
	particle_->CallBarrier();
	emitter_->Update();
	emitter_->Emit(particle_);
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
