#include "Sprite.h"

using namespace Math::Vector;

void Sprite::Initialize(ISpriteState* state, Vector2 pos, Vector2 size)
{
	state_ = state;
	state_->Initialize(this);

	Pos_ = pos;
	if (size.x == 0 && size.y == 0)
	{
		size_ = TextureManager::GetTextureSize(texHandle_);
	}
	else
	{
		size_ = size;
	}
	blendMode_ = BlendNone;
}

void Sprite::Draw(WorldTransform worldTransform)
{
	state_->Draw(this, worldTransform);
}

void Sprite::SetTexHandle(uint32_t texHandle)
{
	texHandle_ = texHandle;
	size_ = TextureManager::GetTextureSize(texHandle);
}

void Sprite::SetSrc(Vector2 TL, Vector2 BL,Vector2 TR, Vector2 BR)
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

	switch (state->GetBlendMode())
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
	default:
		break;
	}
	return PSO;
}