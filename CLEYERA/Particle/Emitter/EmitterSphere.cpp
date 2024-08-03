#include "EmitterSphere.h"

void EmitterSphere::Create(Particle::ParticleEmitter* e)
{
	max_ = e->GetEmitMax();

	sphereBuf_ = make_unique<BufferResource<SEmitterSphere>>();
	sphereBuf_->CreateResource(max_);
	sphereBuf_->CreateInstancingResource(e->GetEmitMax(), e->GetEmitName(), sizeof(SEmitterSphere));
	worldTransform_.resize(max_);


	for (size_t i = 0; i < max_; i++)
	{
		worldTransform_[i].Initialize();
	}

}

void EmitterSphere::Update(Particle::ParticleEmitter* e)
{
	sphereBuf_->Map();
	sphereBuf_->Setbuffer(e->GetSphereParam());

	for (size_t i = 0; i < max_; i++)
	{
		worldTransform_[i].transform.translate = e->GetSphereParam()[i].translate;
		worldTransform_[i].transform.scale =
		{ e->GetSphereParam()[i].radious, e->GetSphereParam()[i].radious, e->GetSphereParam()[i].radious };
		worldTransform_[i].UpdateMatrix();
	}
}

void EmitterSphere::Dispatch(unique_ptr<Particle::GpuParticle>& particle)
{
	SPSOProperty pso = GraphicsPipelineManager::GetInstance()->GetParticle().particleEmitterSphere;
	ComPtr<ID3D12GraphicsCommandList> list = DirectXCommon::GetInstance()->GetCommands().m_pList;
	list->SetComputeRootSignature(pso.rootSignature.Get());
	list->SetPipelineState(pso.GraphicsPipelineState.Get());

	//Ï‚Þ
	particle->CallUavRootparam(0);
	DescriptorManager::GetInstance()->ComputeRootParamerterCommand(1, sphereBuf_->GetSrvIndex());
	RunTimeCounter::GetInstance()->ComputeCommandCall(2);

	DescriptorManager::GetInstance()->ComputeRootParamerterCommand(3, particle->GetfreeCountBuf()->GetSrvIndex());
	list->Dispatch(1, 1, 1);
}

void EmitterSphere::Emit()
{
}

void EmitterSphere::SpownDraw()
{

	ParticleEmitDraw::GetInstance()->SphereDraw(worldTransform_[0]);
}
