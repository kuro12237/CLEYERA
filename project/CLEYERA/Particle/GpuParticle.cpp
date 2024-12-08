#include "GpuParticle.h"

using namespace Engine::Particle;

using namespace Engine::Base::DX;

using namespace Engine::Base::Win;
using namespace Engine::Manager;
using namespace Engine;

void GpuParticle::Create(const size_t kNum, string Name, uint32_t modelHandle)
{
	mulNum = uint32_t(kNum);
	particleNum_ = uint32_t(mulNum) * particleMin;
	name_ = Name;
	modelHandle_ = modelHandle;

	modelHandle;
	vertexBuf_ = make_unique<BufferResource<System::StructData::ParticleVertexData>>();
	indexBuf_ = make_unique<BufferResource<uint32_t>>();

	if (modelHandle_ == 0)
	{
		vertexNum_ = 4;
		indexNum_ = 6;

		vertexParam_.resize(vertexNum_);
		indexParam_.resize(indexNum_);

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
	}
	else
	{
		modelData_ = ModelManager::GetModel(modelHandle_)->GetModelData();
		indexNum_ = static_cast<uint32_t>(modelData_.indecs.size());
		vertexNum_ = static_cast<uint32_t>(modelData_.vertices.size());
		texHandle_ = modelData_.material.handle;

		vertexParam_.resize(vertexNum_);
		indexParam_.resize(indexNum_);
		for (size_t i = 0; i < vertexNum_; i++)
		{
			vertexParam_[i].normal = modelData_.vertices[i].normal;
			vertexParam_[i].position = modelData_.vertices[i].position;
			vertexParam_[i].texcoord = modelData_.vertices[i].texcoord;
		}
		indexParam_ = modelData_.indecs;
	}


	{//頂点作成
		vertexBuf_->CreateResource(vertexNum_);
		vertexBuf_->CreateVertexBufferView();
	}
	{//インデックス作成
		indexBuf_->CreateResource(indexNum_);
		indexBuf_->CreateIndexBufferView();
	}

	{//writeparticleUAV作成
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

	{//頂点マップ
		vertexBuf_->Map();
		vertexBuf_->Setbuffer(vertexParam_);
		vertexBuf_->UnMap();
	}
	{//インデックスマップ
		indexBuf_->Map();
		indexBuf_->Setbuffer(indexParam_);
		indexBuf_->UnMap();
	}

	//Dissolveなどのマテリアルデータを作製
	effectDataBuf_ = make_unique<BufferResource<Particle::System::StructData::EffectData>>();
	effectDataBuf_->CreateResource();


	{//初期化CS_Dispatch
		SPSOProperty pso = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::PARTICLE_INIT, "None");;
		ComPtr<ID3D12GraphicsCommandList>commandList = DirectXCommon::GetInstance()->GetCommands().m_pList;
		ID3D12DescriptorHeap* heap[] = { DirectXCommon::GetInstance()->GetSrvHeap() };
		commandList->SetDescriptorHeaps(1, heap);

		commandList->SetComputeRootSignature(pso.rootSignature.Get());
		commandList->SetPipelineState(pso.GraphicsPipelineState.Get());

		DescriptorManager::GetInstance()->ComputeRootParamerterCommand(0, writeParticleBuf_->GetSrvIndex());
		DescriptorManager::GetInstance()->ComputeRootParamerterCommand(1, freeListIndexBuf_->GetSrvIndex());
		DescriptorManager::GetInstance()->ComputeRootParamerterCommand(2, freeListBuf_->GetSrvIndex());


		UINT dispach = UINT(GetNum() / 1024);
		commandList->Dispatch(dispach, 1, 1);
	}
	DirectXCommon::GetInstance()->CommandClosed();
}

void GpuParticle::Update()
{
	if (drawMode_ == mode_2d)
	{
		Math::Vector::Vector2 srcTR = { 1.0f,0.0f };
		Math::Vector::Vector2 srcBR = { 1.0f,1.0f };
		Math::Vector::Vector2 srcTL = { 0.0f,0.0f };
		Math::Vector::Vector2 srcBL = { 0.0f,1.0f };
		vertexParam_[0].position = { pos_.x,pos_.y + size_.y,0,1 };
		vertexParam_[0].texcoord = srcBL;
		vertexParam_[1].position = { pos_.x ,pos_.y,0,1 };
		vertexParam_[1].texcoord = srcTL;
		vertexParam_[2].position = { pos_.x + size_.x,pos_.y + size_.y,0,1 };
		vertexParam_[2].texcoord = srcBR;
		vertexParam_[3].position = { pos_.x + size_.x,pos_.y,0,1 };
		vertexParam_[3].texcoord = srcTR;
	}
	vertexBuf_->Map();
	vertexBuf_->Setbuffer(vertexParam_);
	vertexBuf_->UnMap();

	effectDataBuf_->Map();
	effectDataBuf_->Setbuffer(effectParam_);
	effectDataBuf_->UnMap();

	//更新CS_Dispatch
	ComPtr<ID3D12GraphicsCommandList>commandList = DirectXCommon::GetInstance()->GetCommands().m_pList;

	SPSOProperty pso = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::PARTICLE_UPDATE, "None");
	commandList->SetComputeRootSignature(pso.rootSignature.Get());
	commandList->SetPipelineState(pso.GraphicsPipelineState.Get());

	DescriptorManager::GetInstance()->ComputeRootParamerterCommand(0, writeParticleBuf_->GetSrvIndex());
	DescriptorManager::GetInstance()->ComputeRootParamerterCommand(1, freeListIndexBuf_->GetSrvIndex());
	DescriptorManager::GetInstance()->ComputeRootParamerterCommand(2, freeListBuf_->GetSrvIndex());


	UINT dispach = UINT(GetNum() / 1024);
	commandList->Dispatch(dispach, 1, 1);

}

void GpuParticle::Draw()
{
	//換える
	SPSOProperty pso;
	if (blend_ == BlendNone)
	{
		if (drawMode_ == DrawMode::mode_3d)
		{
			pso = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::PARTICLE_DRAW, "None3d");
		}
		if (drawMode_ == DrawMode::mode_2d)
		{
			pso = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::PARTICLE_DRAW, "None2d");
		}
	}
	if (blend_ == BlendAdd)
	{
		if (drawMode_ == DrawMode::mode_3d)
		{
			pso = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::PARTICLE_DRAW, "Add3d");
		}
		if (drawMode_ == DrawMode::mode_2d)
		{
			pso = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::PARTICLE_DRAW, "Add2d");
		}
	}

	if (blend_ == DissolveNone)
	{
		if (drawMode_ == DrawMode::mode_3d)
		{
			pso = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::PARTICLE_DRAW, "Add3d");
		}
		if (drawMode_ == DrawMode::mode_2d)
		{
			pso = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::PARTICLE_DRAW, "DissolveNone2d");
		}
	}

	ComPtr<ID3D12GraphicsCommandList>commandList = DirectXCommon::GetInstance()->GetCommands().m_pList;
	commandList->SetGraphicsRootSignature(pso.rootSignature.Get());
	commandList->SetPipelineState(pso.GraphicsPipelineState.Get());

	vertexBuf_->CommandVertexBufferViewCall();
	indexBuf_->CommandIndexBufferViewCall();
	DescriptorManager::GetInstance()->rootParamerterCommand(0, writeParticleBuf_->GetSrvIndex());
	DescriptorManager::GetInstance()->rootParamerterCommand(1, writeParticleBuf_->GetSrvIndex());
	CameraManager::GetInstance()->PsCommandCall(2);
	CameraManager::GetInstance()->VsCommandCall(3);
	DescriptorManager::GetInstance()->rootParamerterCommand(4, texHandle_);

	if (blend_ == DissolveNone)
	{

		if (drawMode_ == DrawMode::mode_2d)
		{
			DescriptorManager::GetInstance()->rootParamerterCommand(5, noiseTexHandle_);
			effectDataBuf_->CommandCall(6);
		}
	}
	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	commandList->DrawIndexedInstanced(indexNum_, UINT(particleNum_), 0, 0, 0);
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

void Particle::GpuParticle::Clear()
{

	{//初期化CS_Dispatch
		SPSOProperty pso = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::PARTICLE_INIT, "None");;
		ComPtr<ID3D12GraphicsCommandList>commandList = DirectXCommon::GetInstance()->GetCommands().m_pList;
		ID3D12DescriptorHeap* heap[] = { DirectXCommon::GetInstance()->GetSrvHeap() };
		commandList->SetDescriptorHeaps(1, heap);

		commandList->SetComputeRootSignature(pso.rootSignature.Get());
		commandList->SetPipelineState(pso.GraphicsPipelineState.Get());

		DescriptorManager::GetInstance()->ComputeRootParamerterCommand(0, writeParticleBuf_->GetSrvIndex());
		DescriptorManager::GetInstance()->ComputeRootParamerterCommand(1, freeListIndexBuf_->GetSrvIndex());
		DescriptorManager::GetInstance()->ComputeRootParamerterCommand(2, freeListBuf_->GetSrvIndex());

		UINT dispach = UINT(GetNum() / 1024);
		commandList->Dispatch(dispach, 1, 1);
	}
	DirectXCommon::GetInstance()->CommandClosed();
}
