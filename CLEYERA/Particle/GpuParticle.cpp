#include "GpuParticle.h"

void GpuParticle::Create(const size_t num, string Name)
{
	particleNum_ = num;
	name_ = Name;

	{//頂点作成
		vertexBuf_ = make_unique<BufferResource<VertexData>>();
		vertexBuf_->CreateResource(vertexNum);
		vertexBuf_->CreateVertexBufferView();
		vertexParam_.resize(vertexNum);
	}
	{//インデックス作成
		indexBuf_ = make_unique<BufferResource<uint32_t>>();
		indexBuf_->CreateResource(indexNum);
		indexBuf_->CreateIndexBufferView();
		indexParam_.resize(indexNum);
	}
	{//particleUAV作成
		particleBuf_ = make_unique<BufferResource<ParticleCS>>();
		particleBuf_->CreateUAVResource(uint32_t(particleNum_), name_,sizeof(ParticleCS));
		particleParam_.resize(particleNum_);
	}

	Math::Vector::Vector2 pos = {0.0f,0.0f};
	Math::Vector::Vector2 size = {1.0f,1.0f};

	vertexParam_[0].position = { pos.x,pos.y + size.y,0,1 };
	vertexParam_[0].texcoord = { 0.0f,1.0f };
	vertexParam_[1].position = { pos.x ,pos.y,0,1 };
	vertexParam_[1].texcoord = { 0.0f,0.0f };
	vertexParam_[2].position = { pos.x + size.x,pos.y + size.y,0,1 };
	vertexParam_[2].texcoord = { 1.0f,1.0f };
	vertexParam_[3].position = { pos.x + size.x,pos.y,0,1 };
	vertexParam_[3].texcoord = { 1.0f,0.0f };

	indexParam_[0] = 0; indexParam_[1] = 1; indexParam_[2] = 2;
	indexParam_[3] = 1; indexParam_[4] = 3; indexParam_[5] = 2;

	vertexBuf_->Map();
	vertexBuf_->Setbuffer(vertexParam_);
	vertexBuf_->UnMap();

	indexBuf_->Map();
	indexBuf_->Setbuffer(indexParam_);
	indexBuf_->UnMap();
	//初期化
	for (size_t i = 0; i < particleNum_; i++)
	{
		particleParam_[i].currentTime = 0;
		particleParam_[i].lifeTime = 60.0f;
		particleParam_[i].translate = {};
		particleParam_[i].scale = { 1.0f,1.0f,1.0f };
		particleParam_[i].velocity = { 0.0f,0.0f,0.0f };
	}
	//particleBuf_->Setbuffer(particleParam_);
}

void GpuParticle::Draw()
{
	//換える
	SPSOProperty pso = GraphicsPipelineManager::GetInstance()->GetPso().Line;

	ComPtr<ID3D12GraphicsCommandList>commandList = DirectXCommon::GetInstance()->GetCommands().m_pList;
	commandList->SetComputeRootSignature(pso.rootSignature.Get());
	commandList->SetPipelineState(pso.GraphicsPipelineState.Get());

	vertexBuf_->CommandVertexBufferViewCall(0);
	indexBuf_->CommandIndexBufferViewCall();
	DescriptorManager::rootParamerterCommand(0,texHandle_);
	particleBuf_->CommandCall(1);
	commandList->Dispatch(1024,1,1);

}
