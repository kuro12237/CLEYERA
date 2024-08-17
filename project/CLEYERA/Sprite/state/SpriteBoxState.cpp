#include "SpriteBoxState.h"

using namespace Math::Vector;

void SpriteBoxState::Initialize(Sprite* state)
{
	CreateResources::CreateBufferResource(sizeof(VertexData) * VertexSize,resource_.Vertex);
	CreateResources::CreateBufferResource(sizeof(Material),resource_.Material);

	resource_.BufferView = CreateResources::VertexCreateBufferView(sizeof(VertexData) * VertexSize, resource_.Vertex.Get(), VertexSize);
	CreateResources::CreateBufferResource(sizeof(uint32_t) * IndexSize, resource_.Index);
	resource_.IndexBufferView = CreateResources::IndexCreateBufferView(sizeof(uint32_t) * IndexSize, resource_.Index.Get());
	state;
}

void SpriteBoxState::Draw(Sprite* state, WorldTransform worldTransform)
{
	VertexData* vertexData = nullptr;
	Material* materialData = nullptr;
	uint32_t* indexData = nullptr;
	resource_.Vertex->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	resource_.Material->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	resource_.Index->Map(0, nullptr, reinterpret_cast<void**>(&indexData));
	Vector2 pos = state->GetPos();
	Vector2 size = state->GetSize();

	vertexData[0].position = { pos.x,pos.y+size.y,0,1 };
	vertexData[0].texcoord = state->GetSrcBL();
	
	vertexData[1].position = { pos.x ,pos.y,0,1 };
	vertexData[1].texcoord = state->GetSrcTL();


	vertexData[2].position = { pos.x + size.x,pos.y+size.y,0,1 };
	vertexData[2].texcoord = state->GetSrcBR();

	vertexData[3].position = { pos.x + size.x,pos.y,0,1 };
	vertexData[3].texcoord = state->GetSrcTR();


	indexData[0] = 0; indexData[1] = 1; indexData[2] = 2;
	indexData[3] = 1; indexData[4] = 3; indexData[5] = 2;

	materialData->color = state->GetColor();
	materialData->uvTransform = Math::Matrix::AffineMatrix(state->GetuvScale(), state->GetuvRotate(), state->GetuvTranslate());
	materialData->dissolveEdgeColor = state->GetDissolveDdgeColor();
	materialData->dissolveMask = state->GetDissolveMask();
	materialData->dissolveEdgeMinMax = state->GetDissolveEdgeMinMax();

	CommandCall(state->GetTexHandle(),state,worldTransform);
}

void SpriteBoxState::CommandCall(uint32_t texHandle,Sprite* state, WorldTransform worldTransform)
{
	Commands commands = DirectXCommon::GetInstance()->GetCommands();

	SPSOProperty PSO = {};

	if (texHandle == 0)
	{
		PSO = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::NONE_2d, "None");;
	}
	else if (!texHandle == 0)
	{
		PSO = state->Get2dSpritePipeline(state);
	}


	commands.m_pList->IASetVertexBuffers(0, 1, &resource_.BufferView);
	commands.m_pList->IASetIndexBuffer(&resource_.IndexBufferView);

	//表示の仕方を設定
	commands.m_pList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//materialDataをgpuへ
	commands.m_pList->SetGraphicsRootConstantBufferView(0, resource_.Material->GetGPUVirtualAddress());

	//worldTransformの行列をgpuへ
	worldTransform.buffer_->CommandCall(1);
	//view行列をgpu
	CameraManager::GetInstance()->CommandCall(2);
	if (!texHandle == 0)
	{
		DescriptorManager::rootParamerterCommand(3, texHandle);
	}

	commands.m_pList->DrawIndexedInstanced(IndexSize, 1, 0, 0, 0);
}
