#pragma once
#include"LogManager.h"
#include"DirectXCommon.h"
#include"ShaderManager.h"
#include"StructGraphicsPipline.h"

#include"SkinningCreatePipline/SkinningCreatePipline.h"
#include"ModelCreatePipline/ModelCreatePipline.h"
#include"PostProcess/CreatePostProcess.h"
#include"SkinningCreateComputePipline/SkinningCreateComputePipline.h"
#include"GpuParticlePipline/CreateGpuParticlePipline.h"

class GraphicsPipelineManager
{
public:

	static GraphicsPipelineManager* GetInstance();

	static void Initialize();

    SPSO GetPso() { return pso; }
	GpuParticlePso  GetParticle() { return gpuParticlePso_; }

#pragma region Get


#pragma endregion

private:


	static void CreateCompute(SPSO& pso);
	static void CreatePSO(SPSO &pso);
	static void Create2dSpritePSOs(SPSO &pso);
	static void Create3dSpritePSOs(SPSO& pso);
	static void Create3dParticlePSOs(SPSO& pso);
	static void CreatePostEffectPSOs(SPSO& pso);

	static SPSOProperty CreateShape(ComPtr<ID3D12Device>device,Commands command,SShaderMode shader);
	static SPSOProperty CreateLine(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreateSprite3dNone(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);

	static SPSOProperty CreatePBR(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreatePhong(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreatePhongNormalModel(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreateSubsurfaceModel(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);

	static SPSOProperty CreateSprite2dNone(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreateSprite2dAdd(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreateSprite2dSubtract(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreateSprite2dMultiply(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreateSprite2dScreen(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);

	static SPSOProperty CreateParticle3dNone(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreateParticle3dAdd(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);

	static SPSOProperty CreatePostEffectTest(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreateShadow(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);

	static void DefferrdShading(SPSO &pso);

	map<Piplines,map<string,SPSOProperty>> piplines_;

	SPSO pso = {};
	GpuParticlePso gpuParticlePso_ = {};
};

