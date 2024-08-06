#include "EmitterSphereState.h"

void EmitterSphere::Create(Particle::ParticleEmitter* e)
{
	max_ = e->GetEmitMax();

	sphereBuf_ = make_unique<BufferResource<Particle::SEmitterSphere>>();
	sphereBuf_->CreateResource(max_);
	sphereBuf_->CreateInstancingResource(e->GetEmitMax(), e->GetEmitName(), sizeof(Particle::SEmitterSphere));
	CreateEmitDraw(max_,e->GetEmitName());
}

void EmitterSphere::Update(Particle::ParticleEmitter* e)
{
	sphereBuf_->Map();
	sphereBuf_->Setbuffer(e->GetSphereParam());
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
	DescriptorManager::GetInstance()->ComputeRootParamerterCommand(3, particle->GetFreeListIndexBuf()->GetSrvIndex());
	DescriptorManager::GetInstance()->ComputeRootParamerterCommand(4, particle->GetFreeListBuf()->GetSrvIndex());
	list->Dispatch(1, 1, 1);
}
