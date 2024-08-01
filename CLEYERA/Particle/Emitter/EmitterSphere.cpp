#include "EmitterSphere.h"

void EmitterSphere::Create(ParticleEmitter*e)
{
	
	max_ = e->GetEmitMax();
	sphereBuf_ = make_unique<BufferResource<SEmitterSphere>>();
	sphereBuf_->CreateResource(e->GetEmitMax());
	sphereBuf_->CreateInstancingResource(e->GetEmitMax(), e->GetEmitName(), sizeof(SEmitterSphere));

}

void EmitterSphere::Update(ParticleEmitter* e)
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
	
	DescriptorManager::GetInstance()->ComputeRootParamerterCommand(3, particle->GetfreeCountBuf()->GetSrvIndex());
	list->Dispatch(UINT(max_ + 1023 / 1024), 1, 1);
}

void EmitterSphere::Emit()
{
}
