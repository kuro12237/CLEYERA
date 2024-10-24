#pragma once
#include"DirectXCommon.h"
#include"StructGraphicsPipline.h"

/// <summary>
/// パイプライン作製用関数
/// </summary>
namespace CreateGraphicsPiplineFanc
{
	void SettingDepth(
		D3D12_DEPTH_STENCIL_DESC& despthStencilDesc,
		bool EnableFlag,
		D3D12_DEPTH_WRITE_MASK writeMask,
		D3D12_COMPARISON_FUNC Func
	);

	void CreateRootSignature(
		ComPtr<ID3D12Device> device,
		D3D12_ROOT_SIGNATURE_DESC& descriptionRootSignature,
		SPSOProperty& result
	);

	/// <summary>
	/// InputElement設定	
	/// </summary>
	/// <param name="inputElementDescs"></param>
	/// <param name="SemanticName"></param>
	/// <param name="SemanticIndex"></param>
	/// <param name="Format"></param>
	/// <param name="AlignedByteOffset"></param>
	void SettingInputElementDesc(
		D3D12_INPUT_ELEMENT_DESC& inputElementDescs,
		LPCSTR SemanticName,
		UINT SemanticIndex,
		DXGI_FORMAT Format,
		UINT AlignedByteOffset
	);

	/// <summary>
	/// ブレンド設定
	/// </summary>
	/// <param name="blenddesc"></param>
	/// <param name="mode"></param>
	void SettingBlendState(
		D3D12_RENDER_TARGET_BLEND_DESC& blenddesc,
		SpriteMode mode);

	/// <summary>
	/// ラスタライザーの設定
	/// </summary>
	/// <param name="rasterizerDesc"></param>
	/// <param name=""></param>
	/// <param name=""></param>
	void SettingRasterizer(
		D3D12_RASTERIZER_DESC& rasterizerDesc,
		D3D12_CULL_MODE CullMode,
		D3D12_FILL_MODE FillMode
	);

}