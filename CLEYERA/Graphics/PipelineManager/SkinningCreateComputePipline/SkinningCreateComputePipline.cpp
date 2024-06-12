#include "SkinningCreateComputePipline.h"

SPSOProperty SkinningCreateComputePipline::CreateSkinningPipline(ComPtr<ID3D12Device> device, Commands commands, SShaderMode shader)
{
	SPSOProperty result;
	D3D12_COMPUTE_PIPELINE_STATE_DESC computePiplineStateDesc{};
	computePiplineStateDesc.CS = {
		.pShaderBytecode = shader.csBlob->GetBufferPointer(),
		.BytecodeLength = shader.csBlob->GetBufferSize()
	};
	CreateSkinningRootSignature(device, result);
	computePiplineStateDesc.pRootSignature = result.rootSignature.Get();
	HRESULT hr = device->CreateComputePipelineState(&computePiplineStateDesc, IID_PPV_ARGS(&result.GraphicsPipelineState));
	assert(SUCCEEDED(hr));
	return SPSOProperty();
}

void SkinningCreateComputePipline::CreateSkinningRootSignature(ComPtr<ID3D12Device> device, SPSOProperty& pso)
{
	D3D12_ROOT_PARAMETER rootParameters[1];
	//skinningPallate
	D3D12_DESCRIPTOR_RANGE descriptorRangeSkinningPallate[1] = {};
	descriptorRangeSkinningPallate[0].BaseShaderRegister = 0;
	descriptorRangeSkinningPallate[0].NumDescriptors = 1;
	descriptorRangeSkinningPallate[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRangeSkinningPallate[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	rootParameters[0].DescriptorTable.pDescriptorRanges = descriptorRangeSkinningPallate;
	rootParameters[0].DescriptorTable.NumDescriptorRanges = _countof(descriptorRangeSkinningPallate);
	//vertex
	D3D12_DESCRIPTOR_RANGE descriptorRangeInputVertex[1] = {};
	descriptorRangeInputVertex[0].BaseShaderRegister = 1;
	descriptorRangeInputVertex[0].NumDescriptors = 1;
	descriptorRangeInputVertex[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRangeInputVertex[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	//rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	//rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	//rootParameters[1].DescriptorTable.pDescriptorRanges = descriptorRangeInputVertex;
	//rootParameters[1].DescriptorTable.NumDescriptorRanges = _countof(descriptorRangeInputVertex);

	////infulence
	//D3D12_DESCRIPTOR_RANGE descriptorRangeinfulence[1] = {};
	//descriptorRangeinfulence[0].BaseShaderRegister = 2;
	//descriptorRangeinfulence[0].NumDescriptors = 1;
	//descriptorRangeinfulence[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	//descriptorRangeinfulence[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	//rootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	//rootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	//rootParameters[2].DescriptorTable.pDescriptorRanges = descriptorRangeinfulence;
	//rootParameters[2].DescriptorTable.NumDescriptorRanges = _countof(descriptorRangeinfulence);

	////output
	//D3D12_DESCRIPTOR_RANGE descriptorRangeOutPutVertex[1] = {};
	//descriptorRangeOutPutVertex[0].BaseShaderRegister = 0;
	//descriptorRangeOutPutVertex[0].NumDescriptors = 1;
	//descriptorRangeOutPutVertex[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	//descriptorRangeOutPutVertex[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	//rootParameters[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	//rootParameters[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	//rootParameters[3].DescriptorTable.pDescriptorRanges = descriptorRangeOutPutVertex;
	//rootParameters[3].DescriptorTable.NumDescriptorRanges = _countof(descriptorRangeOutPutVertex);

	//rootParameters[4].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	//rootParameters[4].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	//rootParameters[4].Descriptor.ShaderRegister = 0;


	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	descriptionRootSignature.Flags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	descriptionRootSignature.pParameters = rootParameters;
	descriptionRootSignature.NumParameters = _countof(rootParameters);

	HRESULT hr = D3D12SerializeRootSignature(&descriptionRootSignature,
		D3D_ROOT_SIGNATURE_VERSION_1, &pso.signatureBlob, &pso.errorBlob);
	if (FAILED(hr))
	{
		LogManager::Log(reinterpret_cast<char*>(pso.errorBlob->GetBufferPointer()));
		assert(false);
	}

	hr = device->CreateRootSignature(0, pso.signatureBlob->GetBufferPointer(),
		pso.signatureBlob->GetBufferSize(), IID_PPV_ARGS(&pso.rootSignature));
}
