#include "Sprite.h"
#include"Utility/RuntimeCounter/RunTimeCounter.h"
using namespace Math::Vector;

using namespace Engine::Base::DX;
using namespace Engine::Base::Win;
using namespace Engine::Objects;
using namespace::Engine::Transform;
using namespace Engine::Camera;
using namespace Engine::Utility;
using namespace Engine::Manager;

void Sprite::Initialize(Vector2 pos, Vector2 size)
{
	pos_ = pos;
	if (size.x == 0 && size.y == 0)
	{
		size_ = TextureManager::GetTextureSize(texHandle_);
	}
	else
	{
		size_ = size;
	}
	blendMode_ = BlendNone;
	CreateBuf();
	vertexDatas_.resize(4);
	indexDatas_.resize(6);
}

void Sprite::Draw(WorldTransform worldTransform)
{
	vertexDatas_[0].position = { pos_.x,pos_.y + size_.y,0,1 };
	vertexDatas_[0].texcoord = srcBL;
	vertexDatas_[1].position = { pos_.x ,pos_.y,0,1 };
	vertexDatas_[1].texcoord = srcTL;
	vertexDatas_[2].position = { pos_.x + size_.x,pos_.y + size_.y,0,1 };
	vertexDatas_[2].texcoord = srcBR;
	vertexDatas_[3].position = { pos_.x + size_.x,pos_.y,0,1 };
	vertexDatas_[3].texcoord = srcTR;

	indexDatas_[0] = 0; indexDatas_[1] = 1; indexDatas_[2] = 2;
	indexDatas_[3] = 1; indexDatas_[4] = 3; indexDatas_[5] = 2;

	materialDatas_.color = color_;
	materialDatas_.uvTransform = Math::Matrix::AffineMatrix(uvScale_, uvRotate_, uvTranslate_);
	materialDatas_.perlinNoiseFactor = perlinNoiseFactor_;
	materialDatas_.perlinNoisePos = perlinNoisePos_;
	materialDatas_.PerlinNoiseScale = PerlinNoiseScale_;

	materialDatas_.dissolveEdgeColor = dissolveEdgeColor_;
	materialDatas_.dissolveMask = dissolveMask_;
	materialDatas_.dissolveEdgeMinMax = dissolveEdgeMinMax_;

	materialDatas_.noiseUvTransform = Math::Matrix::AffineMatrix(noiseUvScale_, noiseUvRotate_, noiseUvTranslate_);
	materialDatas_.perlinNoiseTimer = perlinNoiseTimer_;

	Map();
	vertexBuf_->Setbuffer(vertexDatas_);
	indexBuf_->Setbuffer(indexDatas_);
	materialBuf_->Setbuffer(materialDatas_);
	UnMap();
	if (worldTransform.buffer_)
	{
		CommandCall(worldTransform);
	}
}

void Sprite::SetTexHandle(uint32_t texHandle)
{
	texHandle_ = texHandle;
	size_ = TextureManager::GetTextureSize(texHandle);
}

void Sprite::SetSrc(Vector2 TL, Vector2 BL, Vector2 TR, Vector2 BR)
{
	srcTR = TR;
	srcBR = BR;
	srcTL = TL;
	srcBL = BL;
}


SPSOProperty Sprite::Get2dSpritePipeline(Sprite* state)
{
	SPSOProperty PSO = {};
	Commands commands = DirectXCommon::GetInstance()->GetCommands();

	switch (state->GetSpriteMode())
	{
	case BlendNone:
		PSO = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::SPRITE_2d, "None");
		commands.m_pList->SetGraphicsRootSignature(PSO.rootSignature.Get());
		commands.m_pList->SetPipelineState(PSO.GraphicsPipelineState.Get());

		break;
	case BlendAdd:
		PSO = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::SPRITE_2d, "Add");;
		commands.m_pList->SetGraphicsRootSignature(PSO.rootSignature.Get());
		commands.m_pList->SetPipelineState(PSO.GraphicsPipelineState.Get());
		break;
	case BlendSubtruct:
		PSO = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::SPRITE_2d, "Subtruct");
		commands.m_pList->SetGraphicsRootSignature(PSO.rootSignature.Get());
		commands.m_pList->SetPipelineState(PSO.GraphicsPipelineState.Get());
		break;
	case BlendMultiply:
		PSO = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::SPRITE_2d, "Multiply");
		break;
	case BlendScreen:
		PSO = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::SPRITE_2d, "Screen");
		commands.m_pList->SetGraphicsRootSignature(PSO.rootSignature.Get());
		commands.m_pList->SetPipelineState(PSO.GraphicsPipelineState.Get());
		break;

	case DissolveNone:
		PSO = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::SPRITE_2d, "DissolveNone");
		commands.m_pList->SetGraphicsRootSignature(PSO.rootSignature.Get());
		commands.m_pList->SetPipelineState(PSO.GraphicsPipelineState.Get());
		DescriptorManager::rootParamerterCommand(4, noiseTexHandle_);
		break;
	case PerlineNoise:
		PSO = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::SPRITE_2d, "PerlinNoise");
		commands.m_pList->SetGraphicsRootSignature(PSO.rootSignature.Get());
		commands.m_pList->SetPipelineState(PSO.GraphicsPipelineState.Get());
		RunTimeCounter::GetInstance()->CommandCall(4);

		break;
	default:
		break;
	}
	return PSO;
}


void Sprite::CommandCall(const WorldTransform &worldTransform)
{
	Commands commands = DirectXCommon::GetInstance()->GetCommands();

	SPSOProperty PSO = {};

	if (texHandle_ == 0)
	{
		PSO = GraphicsPipelineManager::GetInstance()->GetPiplines(Pipline::NONE_2d, "None");;
	}
	else if (!texHandle_ == 0)
	{
		PSO = Get2dSpritePipeline(this);
	}

	vertexBuf_->CommandVertexBufferViewCall();
	indexBuf_->CommandIndexBufferViewCall();

	//表示の仕方を設定
	commands.m_pList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//materialDataをgpuへ
	materialBuf_->CommandCall(0);

	//worldTransformの行列をgpuへ
	worldTransform.buffer_->CommandCall(1);
	//view行列をgpu
	CameraManager::GetInstance()->VsCommandCall(2);
	if (!texHandle_ == 0)
	{
		DescriptorManager::rootParamerterCommand(3, texHandle_);
	}

	commands.m_pList->DrawIndexedInstanced(UINT(indexDatas_.size()), 1, 0, 0, 0);
}