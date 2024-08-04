#include "ParticleEmitter.h"

void Particle::ParticleEmitter::CreateType(unique_ptr<IEmitterState> state, unique_ptr<Particle::GpuParticle>& particle)
{
	emitName_ = particle->GetName() + "Emitter";
	sphere_.resize(particle->GetNum());
	type_ = move(state);
	type_->Create(this);

}

void Particle::ParticleEmitter::ImGuiUpdate()
{
	string name = emitName_;
	if (ImGui::TreeNode(name.c_str())) {
		string childName = name+"child";
		ImGui::BeginChild(childName.c_str(), ImVec2(360, 240));
		for (size_t i = 0; i < this->emitMax_; i++)
		{
			string number = to_string(i);
			if (ImGui::TreeNode(number.c_str()))
			{
				ImGui::DragFloat("radious", &sphere_[i].radious, 0.1f);
				ImGui::DragFloat3("t", &sphere_[i].translate.x, 0.1f);
				ImGui::TreePop();
			}
		}
		ImGui::EndChild();
		ImGui::TreePop();
	}
}

void Particle::ParticleEmitter::Update()
{
	sphere_[0].frequency += DeltaTimer(sphere_[0].flame);
	if (sphere_[0].frequency >= sphere_[0].frequencyTime)
	{
		sphere_[0].frequency = 0.0f;
		sphere_[0].emit = 1;
	}
	else
	{
		sphere_[0].emit = 0;
	}

	type_->Update(this);

	auto& wTs = type_->GetWts();
	for (size_t i = 0; i < emitMax_; i++)
	{
		auto& wt = wTs[i];
		wt.transform.translate = sphere_[i].translate;
		wt.transform.scale =
		{ sphere_[i].radious, sphere_[i].radious, sphere_[i].radious };
		wt.UpdateMatrix();
	}
}

void Particle::ParticleEmitter::Emit(unique_ptr<Particle::GpuParticle>& particle)
{
	type_->Dispatch(particle);
}

void Particle::ParticleEmitter::SpownDraw()
{
	type_->SpownDraw();
}
