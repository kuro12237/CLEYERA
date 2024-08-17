#include "CreateGraphicsPiplineFanc.h"

void CreateGraphicsPiplineFanc::SettingDepth(D3D12_DEPTH_STENCIL_DESC& despthStencilDesc, bool EnableFlag, D3D12_DEPTH_WRITE_MASK writeMask, D3D12_COMPARISON_FUNC Func)
{
	despthStencilDesc.DepthEnable = EnableFlag;
	despthStencilDesc.DepthWriteMask = writeMask;
	despthStencilDesc.DepthFunc = Func;
}

void CreateGraphicsPiplineFanc::CreateRootSignature(ComPtr<ID3D12Device> device, D3D12_ROOT_SIGNATURE_DESC& descriptionRootSignature, SPSOProperty& result)
{
	ComPtr<ID3DBlob> signatureBlob = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;
	HRESULT hr = D3D12SerializeRootSignature(&descriptionRootSignature,
		D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
	if (FAILED(hr))
	{
		LogManager::Log(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
		assert(false);
	}

	hr = device->CreateRootSignature(
		0,
		signatureBlob->GetBufferPointer(),
		signatureBlob->GetBufferSize(),
		IID_PPV_ARGS(&result.rootSignature)
	);
	assert(SUCCEEDED(hr));
}

void CreateGraphicsPiplineFanc::SettingInputElementDesc(D3D12_INPUT_ELEMENT_DESC& inputElementDescs, LPCSTR SemanticName, UINT SemanticIndex, DXGI_FORMAT Format, UINT AlignedByteOffset)
{
	inputElementDescs.SemanticName = SemanticName;
	inputElementDescs.SemanticIndex = SemanticIndex;
	inputElementDescs.Format = Format;
	inputElementDescs.AlignedByteOffset = AlignedByteOffset;
}

void CreateGraphicsPiplineFanc::SettingBlendState(D3D12_RENDER_TARGET_BLEND_DESC& blenddesc, SpriteMode mode)
{

	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	blenddesc.BlendEnable = true;

	switch (mode)
	{
	case BlendNone:
		blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
		blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;
		blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;
		blenddesc.BlendOp = D3D12_BLEND_OP_ADD;
		blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
		blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
		break;
	case BlendAdd:
		blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
		blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;
		blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;
		blenddesc.BlendOp = D3D12_BLEND_OP_ADD;
		blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
		blenddesc.DestBlend = D3D12_BLEND_ONE;
		break;
	case BlendSubtruct:
		blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
		blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;
		blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;
		blenddesc.BlendOp = D3D12_BLEND_OP_REV_SUBTRACT;
		blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
		blenddesc.DestBlend = D3D12_BLEND_ONE;
		break;
	case BlendMultiply:
		blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
		blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;
		blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;
		blenddesc.BlendOp = D3D12_BLEND_OP_ADD;
		blenddesc.SrcBlend = D3D12_BLEND_ZERO;
		blenddesc.DestBlend = D3D12_BLEND_SRC_COLOR;
		break;
	case BlendScreen:
		blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
		blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;
		blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;
		blenddesc.BlendOp = D3D12_BLEND_OP_ADD;
		blenddesc.SrcBlend = D3D12_BLEND_INV_DEST_COLOR;
		blenddesc.DestBlend = D3D12_BLEND_ONE;
		break;
	default:
		break;
	}

}

void CreateGraphicsPiplineFanc::SettingRasterizer(D3D12_RASTERIZER_DESC& rasterizerDesc, D3D12_CULL_MODE CullMode, D3D12_FILL_MODE FillMode)
{
	rasterizerDesc.CullMode = CullMode;
	rasterizerDesc.FillMode = FillMode;
}
