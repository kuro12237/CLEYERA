#pragma once
#include"DirectXCommon.h"
struct SPSOProperty
{
	ComPtr<ID3D12PipelineState> GraphicsPipelineState = nullptr;
	ComPtr<ID3D12RootSignature> rootSignature = nullptr;
	ComPtr<ID3DBlob> signatureBlob = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;

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
	SBlendPSO Particle3d;
	SPSOProperty PBR_Model;
	SPSOProperty Phong_Model;
	SPSOProperty PhongNormal_Model;
	SPSOProperty PhongSubsurface_Model;
	SBlendPSO LightingParticle3d;
	SPSOProperty PostEffectTest;
	SPSOProperty shadow;
};

enum  BlendMode
{
	BlendNone,
	BlendAdd,
	BlendSubtruct,
	BlendMultiply,
	BlendScreen,
};
