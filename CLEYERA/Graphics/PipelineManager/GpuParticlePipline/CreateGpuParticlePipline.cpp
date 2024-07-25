#include "CreateGpuParticlePipline.h"

SPSOProperty CreateGpuParticle::CreateGpuParticle_Init(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader)
{
	SPSOProperty pso = {};

	D3D12_COMPUTE_PIPELINE_STATE_DESC psoDesc = {};
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	HRESULT hr = {};
	//rootsignature作成
	descriptionRootSignature.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	D3D12_ROOT_PARAMETER rootParameters[1] = {};

	//u0 : tパラメーターuav
	D3D12_DESCRIPTOR_RANGE descriptorRange = {};
	descriptorRange.BaseShaderRegister = 0;
	descriptorRange.NumDescriptors = 1;
	descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	rootParameters[0].DescriptorTable.pDescriptorRanges = &descriptorRange;
	rootParameters[0].DescriptorTable.NumDescriptorRanges = 1;

	descriptionRootSignature.pParameters = rootParameters;
	descriptionRootSignature.NumParameters = _countof(rootParameters);

	//rootsignatureの作成
	assert(shader.csBlob != nullptr);
	hr = D3D12SerializeRootSignature(&descriptionRootSignature,
		D3D_ROOT_SIGNATURE_VERSION_1, &pso.signatureBlob, &pso.errorBlob);
	if (FAILED(hr))
	{
		LogManager::Log(reinterpret_cast<char*>(pso.errorBlob->GetBufferPointer()));
		assert(false);
	}
	hr = device->CreateRootSignature(0, pso.signatureBlob->GetBufferPointer(),
		pso.signatureBlob->GetBufferSize(), IID_PPV_ARGS(&pso.rootSignature));
	assert(SUCCEEDED(hr));

	//psoの作成
	psoDesc.CS = {
	.pShaderBytecode = shader.csBlob->GetBufferPointer(),
	.BytecodeLength = shader.csBlob->GetBufferSize()
	};
	psoDesc.pRootSignature = pso.rootSignature.Get();
	psoDesc.NodeMask = 0;
	hr = device->CreateComputePipelineState(&psoDesc, IID_PPV_ARGS(&pso.GraphicsPipelineState));
	assert(SUCCEEDED(hr));

	return pso;
}