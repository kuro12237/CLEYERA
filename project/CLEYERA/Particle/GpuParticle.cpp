#include "GpuParticle.h"

using namespace Particle;

void GpuParticle::Create(const size_t kNum, string Name)
{
	particleNum_ = kNum * particleMin;
	name_ = Name;

	{//���_�쐬
		vertexBuf_ = make_unique<BufferResource<System::StructData::ParticleVertexData>>();
		vertexBuf_->CreateResource(vertexNum);
		vertexBuf_->CreateVertexBufferView();
		vertexParam_.resize(vertexNum);
	}
	{//�C���f�b�N�X�쐬
		indexBuf_ = make_unique<BufferResource<uint32_t>>();
		indexBuf_->CreateResource(indexNum);
		indexBuf_->CreateIndexBufferView();
		indexParam_.resize(indexNum);
	}
	{//writeparticleUAV�쐬
		writeParticleBuf_ = make_unique<BufferResource<ParticleCS>>();
		writeParticleBuf_->CreateUAVResource(uint32_t(particleNum_), name_ + "_Write", sizeof(ParticleCS));
		writeParticleParam_.resize(particleNum_);
	}
	{//freeListIndex
		freeListIndexBuf_ = make_unique<BufferResource<uint32_t>>();
		freeListIndexBuf_->CreateResource(uint32_t(particleNum_));
		freeListIndexBuf_->CreateUAVResource(uint32_t(particleNum_), name_ + "_freeListIndex", sizeof(int32_t));
		freeListIndex_.resize(particleNum_);
	}
	{//freeList
		freeListBuf_ = make_unique<BufferResource<uint32_t>>();
		freeListBuf_->CreateResource(uint32_t(particleNum_));
		freeListBuf_->CreateUAVResource(uint32_t(particleNum_), name_ + "_freeList", sizeof(int32_t));
		freeList_.resize(particleNum_);
	}
	{//���_�̏�����
		vertexParam_[0].position = { -1.0f,-1.0f,0,1 };
		vertexParam_[0].texcoord = { 0.0f,1.0f };
		vertexParam_[1].position = { 1.0f ,1.0f,0,1 };
		vertexParam_[1].texcoord = { 0.0f,0.0f };
		vertexParam_[2].position = { 1.0f,-1.0f,0,1 };
		vertexParam_[2].texcoord = { 1.0f,1.0f };
		vertexParam_[3].position = { -1.0f,1.0f,0,1 };
		vertexParam_[3].texcoord = { 1.0f,0.0f };
	}
	{//�C���f�b�N�X�̏�����
		indexParam_[0] = 0; indexParam_[1] = 1; indexParam_[2] = 2;
		indexParam_[3] = 0; indexParam_[4] = 3; indexParam_[5] = 1;
	}

	vertexParam_[0].position = { -1.0f,-1.0f,0,1 };
	vertexParam_[0].texcoord = { 0.0f,1.0f };
	vertexParam_[1].position = { -1.0f ,1.0f,0,1 };
	vertexParam_[1].texcoord = { 0.0f,0.0f };
	vertexParam_[2].position = { 1.0f,-1.0f,0,1 };
	vertexParam_[2].texcoord = { 1.0f,1.0f };
	vertexParam_[3].position = { 1.0f,1.0f,0,1 };
	vertexParam_[3].texcoord = { 1.0f,0.0f };


	indexParam_[0] = 0; indexParam_[1] = 1; indexParam_[2] = 2;
	indexParam_[3] = 1; indexParam_[4] = 3; indexParam_[5] = 2;
	{//���_�}�b�v
		vertexBuf_->Map();
		vertexBuf_->Setbuffer(vertexParam_);
		vertexBuf_->UnMap();
	}
	{//�C���f�b�N�X�}�b�v
		indexBuf_->Map();
		indexBuf_->Setbuffer(indexParam_);
		indexBuf_->UnMap();
	}

	{//������CS_Dispatch
		SPSOProperty pso = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::PARTICLE_INIT, "None");;
		ComPtr<ID3D12GraphicsCommandList>commandList = DirectXCommon::GetInstance()->GetCommands().m_pList;
		ID3D12DescriptorHeap* heap[] = { DirectXCommon::GetInstance()->GetSrvHeap() };
		commandList->SetDescriptorHeaps(1, heap);

		commandList->SetComputeRootSignature(pso.rootSignature.Get());
		commandList->SetPipelineState(pso.GraphicsPipelineState.Get());

		DescriptorManager::GetInstance()->ComputeRootParamerterCommand(0, writeParticleBuf_->GetSrvIndex());
		DescriptorManager::GetInstance()->ComputeRootParamerterCommand(1, freeListIndexBuf_->GetSrvIndex());
		DescriptorManager::GetInstance()->ComputeRootParamerterCommand(2, freeListBuf_->GetSrvIndex());

		commandList->Dispatch(UINT(particleNum_ + 1023 / 1024), 1, 1);
	}
	DirectXCommon::GetInstance()->CommandClosed();
}

void GpuParticle::Update()
{
	{//������CS_Dispatch
		ComPtr<ID3D12GraphicsCommandList>commandList = DirectXCommon::GetInstance()->GetCommands().m_pList;

		SPSOProperty pso = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::PARTICLE_UPDATE , "None");
		commandList->SetComputeRootSignature(pso.rootSignature.Get());
		commandList->SetPipelineState(pso.GraphicsPipelineState.Get());

		DescriptorManager::GetInstance()->ComputeRootParamerterCommand(0, writeParticleBuf_->GetSrvIndex());
		DescriptorManager::GetInstance()->ComputeRootParamerterCommand(1, freeListIndexBuf_->GetSrvIndex());
		DescriptorManager::GetInstance()->ComputeRootParamerterCommand(2, freeListBuf_->GetSrvIndex());

		commandList->Dispatch(UINT(particleNum_ + 1023 / 1024), 1, 1);
	}
}

void GpuParticle::Draw()
{
	//������
	SPSOProperty pso = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::PARTICLE_DRAW, "None");

	ComPtr<ID3D12GraphicsCommandList>commandList = DirectXCommon::GetInstance()->GetCommands().m_pList;
	commandList->SetGraphicsRootSignature(pso.rootSignature.Get());
	commandList->SetPipelineState(pso.GraphicsPipelineState.Get());

	vertexBuf_->CommandVertexBufferViewCall();
	indexBuf_->CommandIndexBufferViewCall();
	DescriptorManager::GetInstance()->rootParamerterCommand(0, writeParticleBuf_->GetSrvIndex());
	DescriptorManager::GetInstance()->rootParamerterCommand(1, writeParticleBuf_->GetSrvIndex());
	CameraManager::GetInstance()->CommandCall(2);
	CameraManager::GetInstance()->CommandCall(3);
	DescriptorManager::GetInstance()->rootParamerterCommand(4, texHandle_);

	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	commandList->DrawIndexedInstanced(6, UINT(particleNum_), 0, 0, 0);
}

void GpuParticle::CallBarrier()
{
	ComPtr<ID3D12GraphicsCommandList>commandList = DirectXCommon::GetInstance()->GetCommands().m_pList;
	D3D12_RESOURCE_BARRIER barrier{};
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_UAV;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.UAV.pResource = writeParticleBuf_->GetBuffer();
	commandList->ResourceBarrier(1, &barrier);
}

void GpuParticle::CallUavRootparam(uint32_t rootParamIndex)
{
	DescriptorManager::GetInstance()->ComputeRootParamerterCommand(rootParamIndex, writeParticleBuf_->GetSrvIndex());
}