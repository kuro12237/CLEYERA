#pragma once
#include"LogManager.h"
#include"DirectXCommon.h"
#include"ShaderManager.h"
#include"StructGraphicsPipline.h"

#include"ModelCreatePipline/ModelCreatePipline.h"
#include"GpuParticlePipline/CreateGpuParticlePipline.h"
#include"Sprite_2dPipline/Sprite_2d_CreatePipline.h"
#include"Phong_CreatePipline/Phong_CreatePipline.h"

/// <summary>
/// パイプラインを登録管理
/// </summary>
class GraphicsPipelineManager
{
public:

	static GraphicsPipelineManager* GetInstance();

	void Initialize();

#pragma region Get
	SPSOProperty GetPiplines(Pipline::Piplines pipline, string mode) { return piplines_[pipline][mode]; };
#pragma endregion

private:

#pragma region 登録関数

	/// <summary>
/// シェイプ用のパイプラインステートオブジェクトを作成する関数
/// </summary>
	static SPSOProperty CreateShape(ComPtr<ID3D12Device> device, Engine::Base::DX::Commands command, SShaderMode shader);

	/// <summary>
	/// ライン描画用のパイプラインステートオブジェクトを作成する関数
	/// </summary>
	static SPSOProperty CreateLine(ComPtr<ID3D12Device> device, Engine::Base::DX::Commands commands, SShaderMode shader);

	/// <summary>
	/// 3Dスプライト（通常描画）用のパイプラインステートオブジェクトを作成する関数
	/// </summary>
	static SPSOProperty CreateSprite3dNone(ComPtr<ID3D12Device> device, Engine::Base::DX::Commands commands, SShaderMode shader);

	/// <summary>
	/// 3Dスプライト（加算合成+デプス書き込みあり）用のパイプラインステートオブジェクトを作成する関数
	/// </summary>
	static SPSOProperty CreateSprite3dAddNoneWriteDepth(ComPtr<ID3D12Device> device, Engine::Base::DX::Commands commands, SShaderMode shader);

	/// <summary>
	/// 3Dパーティクル（通常描画）用のパイプラインステートオブジェクトを作成する関数
	/// </summary>
	static SPSOProperty CreateParticle3dNone(ComPtr<ID3D12Device> device, Engine::Base::DX::Commands commands, SShaderMode shader);

	/// <summary>
	/// 3Dパーティクル（加算合成）用のパイプラインステートオブジェクトを作成する関数
	/// </summary>
	static SPSOProperty CreateParticle3dAdd(ComPtr<ID3D12Device> device, Engine::Base::DX::Commands commands, SShaderMode shader);

	/// <summary>
	/// ポストエフェクトテスト用のパイプラインステートオブジェクトを作成する関数
	/// </summary>
	static SPSOProperty CreatePostEffectTest(ComPtr<ID3D12Device> device, Engine::Base::DX::Commands commands, SShaderMode shader);

#pragma endregion

	map<Pipline::Piplines, map<string, SPSOProperty>> piplines_;

#pragma region
	GraphicsPipelineManager() = default;
	~GraphicsPipelineManager() = default;
	GraphicsPipelineManager(const GraphicsPipelineManager&) = delete;
	const GraphicsPipelineManager& operator=(const GraphicsPipelineManager&) = delete;
#pragma endregion 
};

