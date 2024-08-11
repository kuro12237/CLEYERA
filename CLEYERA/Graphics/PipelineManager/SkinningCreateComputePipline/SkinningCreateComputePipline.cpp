#include "SkinningCreateComputePipline.h"

SPSOProperty SkinningCreateComputePipline::CreateSkinningPipline(ComPtr<ID3D12Device> device, Commands commands, SShaderMode shader)
{
	SPSOProperty result;
	D3D12_COMPUTE_PIPELINE_STATE_DESC computePiplineStateDesc{};
	computePiplineStateDesc.CS = {
		.pShaderBytecode = shader.csBlob->GetBufferPointer(),
		.BytecodeLength = shader.csBlob->GetBufferSize()
	};
	CreateSkinningRootSignature(result);
	computePiplineStateDesc.pRootSignature = result.rootSignature.Get();
	HRESULT hr;
	hr = device->CreateComputePipelineState(&computePiplineStateDesc, IID_PPV_ARGS(&result.GraphicsPipelineState));
	assert(SUCCEEDED(hr));
	return result;
}

void SkinningCreateComputePipline::CreateSkinningRootSignature(SPSOProperty& pso)
{
    D3D12_ROOT_PARAMETER rootParameters[5] = {};

	// 0: MatrixPalette
	D3D12_DESCRIPTOR_RANGE descriptorRangeForMatrixPalette[1] = {};
	descriptorRangeForMatrixPalette[0].BaseShaderRegister = 0;
	descriptorRangeForMatrixPalette[0].NumDescriptors = 1;
	descriptorRangeForMatrixPalette[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRangeForMatrixPalette[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	rootParameters[0].DescriptorTable.pDescriptorRanges = descriptorRangeForMatrixPalette;
	rootParameters[0].DescriptorTable.NumDescriptorRanges = _countof(descriptorRangeForMatrixPalette);

	// 1: InputVertices
	D3D12_DESCRIPTOR_RANGE descriptorRangeForInputVertices[1] = {};
	descriptorRangeForInputVertices[0].BaseShaderRegister = 1;
	descriptorRangeForInputVertices[0].NumDescriptors = 1;
	descriptorRangeForInputVertices[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRangeForInputVertices[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	rootParameters[1].DescriptorTable.pDescriptorRanges = descriptorRangeForInputVertices;
	rootParameters[1].DescriptorTable.NumDescriptorRanges = _countof(descriptorRangeForInputVertices);

	// 2: Influences
	D3D12_DESCRIPTOR_RANGE descriptorRangeForInfluences[1] = {};
	descriptorRangeForInfluences[0].BaseShaderRegister = 2;
	descriptorRangeForInfluences[0].NumDescriptors = 1;
	descriptorRangeForInfluences[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRangeForInfluences[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	rootParameters[2].DescriptorTable.pDescriptorRanges = descriptorRangeForInfluences;
	rootParameters[2].DescriptorTable.NumDescriptorRanges = _countof(descriptorRangeForInfluences);

	// 3: OutputVertices
	D3D12_DESCRIPTOR_RANGE descriptorRangeForOutputVertices[1] = {};
	descriptorRangeForOutputVertices[0].BaseShaderRegister = 0;
	descriptorRangeForOutputVertices[0].NumDescriptors = 1;
	descriptorRangeForOutputVertices[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	descriptorRangeForOutputVertices[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	rootParameters[3].DescriptorTable.pDescriptorRanges = descriptorRangeForOutputVertices;
	rootParameters[3].DescriptorTable.NumDescriptorRanges = _countof(descriptorRangeForOutputVertices);

	// 4: SkinningInformation
	rootParameters[4].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[4].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	rootParameters[4].Descriptor.ShaderRegister = 0;


	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	descriptionRootSignature.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	descriptionRootSignature.pParameters = rootParameters;
	descriptionRootSignature.NumParameters = _countof(rootParameters);
	descriptionRootSignature.pStaticSamplers = nullptr;

	ComPtr<ID3DBlob> signatureBlob = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;
	HRESULT hr = D3D12SerializeRootSignature(&descriptionRootSignature,
		D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
	if (FAILED(hr))
	{
		LogManager::Log(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
		assert(false);
	}

	hr = DirectXCommon::GetInstance()->GetDevice()->CreateRootSignature(0, signatureBlob->GetBufferPointer(),
		signatureBlob->GetBufferSize(), IID_PPV_ARGS(&pso.rootSignature));
	assert(SUCCEEDED(hr));
}
