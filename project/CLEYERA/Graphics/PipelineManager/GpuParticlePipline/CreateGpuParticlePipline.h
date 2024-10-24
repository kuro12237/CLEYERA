#pragma once
#include"StructGraphicsPipline.h"
#include"CreateGraphicsPiplineFanc.h"
#include"ShaderManager.h"

/// <summary>
/// GPUパイプライン作製関数
/// </summary>
class CreateGpuParticle
{
public:
	/// <summary>
/// GPUパーティクルの初期化用パイプラインステートオブジェクトを作成する関数
/// </summary>
	static SPSOProperty CreateGpuParticle_Init(ComPtr<ID3D12Device>device, Engine::Base::DX::Commands commands, SShaderMode shader);

	/// <summary>
	/// 描画なしのGPUパーティクル用パイプラインステートオブジェクトを作成する関数
	/// </summary>
	static SPSOProperty CreateGpuParticle_NoneDraw(ComPtr<ID3D12Device>device, Engine::Base::DX::Commands commands, SShaderMode shader);

	/// <summary>
	/// 加算描画を行うGPUパーティクル用パイプラインステートオブジェクトを作成する関数
	/// </summary>
	static SPSOProperty CreateGpuParticle_AddDraw(ComPtr<ID3D12Device>device, Engine::Base::DX::Commands commands, SShaderMode shader);

	/// <summary>
	/// ディゾルブ効果付きのGPUパーティクル用パイプラインステートオブジェクトを作成する関数
	/// </summary>
	static SPSOProperty CreateGpuParticle_DissolveNoneDraw(ComPtr<ID3D12Device>device, Engine::Base::DX::Commands commands, SShaderMode shader);

	/// <summary>
	/// GPUパーティクルの更新用パイプラインステートオブジェクトを作成する関数
	/// </summary>
	static SPSOProperty CreateGpuParticle_Update(ComPtr<ID3D12Device>device, Engine::Base::DX::Commands commands, SShaderMode shader);

	/// <summary>
	/// 球形エミッターを持つGPUパーティクル用パイプラインステートオブジェクトを作成する関数
	/// </summary>
	static SPSOProperty CreateGpuParticcle_Emitter_Sphere(ComPtr<ID3D12Device>device, Engine::Base::DX::Commands commands, SShaderMode shader);

	/// <summary>
	/// ボックス形エミッターを持つGPUパーティクル用パイプラインステートオブジェクトを作成する関数
	/// </summary>
	static SPSOProperty CreateGpuParticcle_Emitter_Box(ComPtr<ID3D12Device>device, Engine::Base::DX::Commands commands, SShaderMode shader);

	/// <summary>
	/// 吸引フィールドを持つGPUパーティクル用パイプラインステートオブジェクトを作成する関数
	/// </summary>
	static SPSOProperty CreateGpuParticle_Field_Suction(ComPtr<ID3D12Device>device, Engine::Base::DX::Commands commands, SShaderMode shader);

private:

};
