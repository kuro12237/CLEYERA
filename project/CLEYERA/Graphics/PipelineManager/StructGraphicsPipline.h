#pragma once
#include"DirectXCommon.h"

/// <summary>
/// パイプラインデータ
/// </summary>
namespace Pipline
{
	enum Piplines
	{
		NONE_2d,
		NONE_3d,
		SPRITE_2d,
		SPRITE_3d,
		LINE_3d,
		PRIMITIVE,
		SKYBOX,
		POST_EFFECT,
		PHONG,
		PBR,
		PARTICLE_EMITTER,
		PARTICLE_DRAW,
		PARTICLE_INIT,
		PARTICLE_UPDATE,
		PARTICLE_FIELD
	};
}
struct SPSOProperty
{
	ComPtr<ID3D12PipelineState> GraphicsPipelineState = nullptr;
	ComPtr<ID3D12RootSignature> rootSignature = nullptr;
};

struct  SBlendPSO
{
	SPSOProperty none;
	SPSOProperty Add;
	SPSOProperty Subtruct;
	SPSOProperty Multiply;
	SPSOProperty Screen;

};

struct SPSO
{
	SPSOProperty shape;
	SPSOProperty Line;
	SBlendPSO Sprite2d;
	SBlendPSO Sprite3d;
	SPSOProperty PBR_Model;
	SPSOProperty PhongNormal_Model;
	SPSOProperty PhongSubsurface_Model;
	SPSOProperty phongNormalInstancing_Model;
	SPSOProperty ColorPostProcess;
	SPSOProperty PostEffect;
	SPSOProperty Phong_SkinningModel;
	SPSOProperty SkyBox;
	SPSOProperty skinningCompute;
};

struct GpuParticlePso {
	SPSOProperty particleInit;
	SPSOProperty particleUpdate;
	SPSOProperty particleEmitterSphere;
	SPSOProperty particleEmitterBox;
	//Draw
	SPSOProperty debugDraw;
};

enum  SpriteMode
{
	BlendNone,
	BlendAdd,
	BlendSubtruct,
	BlendMultiply,
	BlendScreen,
	DissolveNone,
	PerlineNoise
};
