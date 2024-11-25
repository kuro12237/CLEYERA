#pragma once
#include"Graphics/PipelineManager/StructGraphicsPipline.h"
#include"CreateGraphicsPiplineFanc.h"
#include"ShaderManager.h"

/// <summary>
/// Phongパイプライン作製関数
/// </summary>
class Phong_CreatePipline
{
public:

	static Phong_CreatePipline* GetInstance();

	void Initialize();
	/// <summary>
    /// Phongライティングの法線マッピングモデル用パイプラインステートオブジェクトを作成する関数
    /// </summary>
	SPSOProperty CreatePhongNormalModel(SShaderMode shader);

	/// <summary>
	/// ディゾルブエフェクト付き法線マッピングモデル用パイプラインステートオブジェクトを作成する関数
	/// </summary>
	SPSOProperty CreateDissolveNormalModel(SShaderMode shader, D3D12_RASTERIZER_DESC rasterRizer);

	/// <summary>
	/// サブサーフェス・スキャタリングモデル用パイプラインステートオブジェクトを作成する関数
	/// </summary>
	SPSOProperty CreateSubsurfaceModel(SShaderMode shader);

	/// <summary>
	/// インスタンシングモデル用パイプラインステートオブジェクトを作成する関数
	/// </summary>
	SPSOProperty CreateInstancingModel(SShaderMode shader);

	/// <summary>
	/// スキニングモデル用パイプラインステートオブジェクトを作成する関数
	/// </summary>
	SPSOProperty CreateSkinningModel(SShaderMode shader, bool isDepthWrite = true);



private:
	ComPtr<ID3D12Device>device = nullptr;
	ComPtr<ID3D12GraphicsCommandList>commandList_ = nullptr;
};
