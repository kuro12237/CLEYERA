#pragma once
#include"Graphics/PipelineManager/StructGraphicsPipline.h"
#include"CreateGraphicsPiplineFanc.h"
#include"ShaderManager.h"

/// <summary>
/// 2dのパイプライン作製関数
/// </summary>
class Sprite_2d_CreatePipline
{
public:

	static Sprite_2d_CreatePipline* GetInstance();

	void Initialize();
	/// <summary>
    /// 通常描画用のパイプラインステートオブジェクトを作成する関数
    /// </summary>
	SPSOProperty CreateNone(SShaderMode shader);

	/// <summary>
	/// 加算合成描画用のパイプラインステートオブジェクトを作成する関数
	/// </summary>
	SPSOProperty CreateAdd(SShaderMode shader);

	/// <summary>
	/// 減算合成描画用のパイプラインステートオブジェクトを作成する関数
	/// </summary>
	SPSOProperty CreateSubtract(SShaderMode shader);

	/// <summary>
	/// 乗算合成描画用のパイプラインステートオブジェクトを作成する関数
	/// </summary>
	SPSOProperty CreateMultiply(SShaderMode shader);

	/// <summary>
	/// スクリーン合成描画用のパイプラインステートオブジェクトを作成する関数
	/// </summary>
	SPSOProperty CreateScreen(SShaderMode shader);

	/// <summary>
	/// ディゾルブエフェクト（通常描画）用のパイプラインステートオブジェクトを作成する関数
	/// </summary>
	SPSOProperty CreateDissolveNone(SShaderMode shader);

	/// <summary>
	/// パーリンノイズエフェクト用のパイプラインステートオブジェクトを作成する関数
	/// </summary>
	SPSOProperty CreatePerlinNoise(SShaderMode shader);

private:
	ComPtr<ID3D12Device>device = nullptr;
	ComPtr<ID3D12GraphicsCommandList>commandList_ = nullptr;
};

