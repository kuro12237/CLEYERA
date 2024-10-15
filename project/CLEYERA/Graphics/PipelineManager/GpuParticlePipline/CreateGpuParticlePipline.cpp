#include "CreateGpuParticlePipline.h"

using namespace Engine::Base::DX;

SPSOProperty CreateGpuParticle::CreateGpuParticle_Init(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader)
{
	SPSOProperty pso = {};

	D3D12_COMPUTE_PIPELINE_STATE_DESC psoDesc = {};
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	HRESULT hr = {};
	//rootsignature作成
	descriptionRootSignature.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	D3D12_ROOT_PARAMETER rootParameters[3] = {};

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

	//u1 : freeCountuav
	D3D12_DESCRIPTOR_RANGE descriptorRange_freeCount = {};
	descriptorRange_freeCount.BaseShaderRegister = 1;
	descriptorRange_freeCount.NumDescriptors = 1;
	descriptorRange_freeCount.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	descriptorRange_freeCount.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	rootParameters[1].DescriptorTable.pDescriptorRanges = &descriptorRange_freeCount;
	rootParameters[1].DescriptorTable.NumDescriptorRanges = 1;

	//u2 : freeList
	D3D12_DESCRIPTOR_RANGE descriptorRange_freeList = {};
	descriptorRange_freeList.BaseShaderRegister = 2;
	descriptorRange_freeList.NumDescriptors = 1;
	descriptorRange_freeList.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	descriptorRange_freeList.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	rootParameters[2].DescriptorTable.pDescriptorRanges = &descriptorRange_freeList;
	rootParameters[2].DescriptorTable.NumDescriptorRanges = 1;

	descriptionRootSignature.pParameters = rootParameters;
	descriptionRootSignature.NumParameters = _countof(rootParameters);
	ComPtr<ID3DBlob> signatureBlob = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;
	//rootsignatureの作成
	assert(shader.csBlob != nullptr);
	hr = D3D12SerializeRootSignature(&descriptionRootSignature,
		D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
	if (FAILED(hr))
	{
		LogManager::Log(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
		assert(false);
	}
	hr = device->CreateRootSignature(0, signatureBlob->GetBufferPointer(),
		signatureBlob->GetBufferSize(), IID_PPV_ARGS(&pso.rootSignature));
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

SPSOProperty CreateGpuParticle::CreateGpuParticle_NoneDraw(ComPtr<ID3D12Device> device, Commands commands, SShaderMode shader)
{

	SPSOProperty pso;
	HRESULT hr = {};

	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	D3D12_BLEND_DESC blendDesc{};
	D3D12_RASTERIZER_DESC rasterizerDesc{};
	D3D12_DEPTH_STENCIL_DESC despthStencilDesc{};
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};

	//rootsignature作成
	descriptionRootSignature.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	D3D12_ROOT_PARAMETER rootParameters[5] = {};
	//u0 : VS param uav
	D3D12_DESCRIPTOR_RANGE descriptorRangeVS_UAV[1] = {};
	descriptorRangeVS_UAV[0].BaseShaderRegister = 0;
	descriptorRangeVS_UAV[0].NumDescriptors = 1;
	descriptorRangeVS_UAV[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	descriptorRangeVS_UAV[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rootParameters[0].DescriptorTable.pDescriptorRanges = descriptorRangeVS_UAV;
	rootParameters[0].DescriptorTable.NumDescriptorRanges = _countof(descriptorRangeVS_UAV);

	//u1 : PS param uav
	D3D12_DESCRIPTOR_RANGE descriptorRangePS_UAV[1] = {};
	descriptorRangePS_UAV[0].BaseShaderRegister = 0;
	descriptorRangePS_UAV[0].NumDescriptors = 1;
	descriptorRangePS_UAV[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	descriptorRangePS_UAV[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[1].DescriptorTable.pDescriptorRanges = descriptorRangePS_UAV;
	rootParameters[1].DescriptorTable.NumDescriptorRanges = _countof(descriptorRangePS_UAV);

	//b0 : VSに送るカメラ

	rootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rootParameters[2].Descriptor.ShaderRegister = 0;

	//b0 : PSに送るカメラ
	rootParameters[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[3].Descriptor.ShaderRegister = 0;

	//テクスチャ
	D3D12_DESCRIPTOR_RANGE descriptorRangePS_Tex[1] = {};
	descriptorRangePS_Tex[0].BaseShaderRegister = 0;
	descriptorRangePS_Tex[0].NumDescriptors = 1;
	descriptorRangePS_Tex[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRangePS_Tex[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[4].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[4].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[4].DescriptorTable.pDescriptorRanges = descriptorRangePS_Tex;
	rootParameters[4].DescriptorTable.NumDescriptorRanges = _countof(descriptorRangePS_Tex);

	D3D12_STATIC_SAMPLER_DESC staticSamplers[1] = {};
	//Sampler
	staticSamplers[0].Filter = D3D12_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	staticSamplers[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;

	staticSamplers[0].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	staticSamplers[0].MaxLOD = D3D12_FLOAT32_MAX;
	staticSamplers[0].ShaderRegister = 0;
	staticSamplers[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;


	descriptionRootSignature.pParameters = rootParameters;
	descriptionRootSignature.NumParameters = _countof(rootParameters);

	descriptionRootSignature.pStaticSamplers = staticSamplers;
	descriptionRootSignature.NumStaticSamplers = _countof(staticSamplers);
	ComPtr<ID3DBlob> signatureBlob = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;
	hr = D3D12SerializeRootSignature(&descriptionRootSignature,
		D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
	if (FAILED(hr))
	{
		LogManager::Log(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
		assert(false);
	}
	hr = device->CreateRootSignature(0, signatureBlob->GetBufferPointer(),
		signatureBlob->GetBufferSize(), IID_PPV_ARGS(&pso.rootSignature));
	assert(SUCCEEDED(hr));

	//InputLayOut作成
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[4] = {};
	//pos
	inputElementDescs[0].SemanticName = "POSITION";
	inputElementDescs[0].SemanticIndex = 0;
	inputElementDescs[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	inputElementDescs[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

	//texCoord
	inputElementDescs[1].SemanticName = "TEXCOORD";
	inputElementDescs[1].SemanticIndex = 0;
	inputElementDescs[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	inputElementDescs[1].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

	//normal
	inputElementDescs[2].SemanticName = "NORMAL";
	inputElementDescs[2].SemanticIndex = 0;
	inputElementDescs[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	inputElementDescs[2].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

	//instancedId
	inputElementDescs[3].SemanticName = "INSTANCEID";
	inputElementDescs[3].SemanticIndex = 0;
	inputElementDescs[3].Format = DXGI_FORMAT_R32_UINT;
	inputElementDescs[3].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;


	inputLayoutDesc.pInputElementDescs = inputElementDescs;
	inputLayoutDesc.NumElements = _countof(inputElementDescs);

	//Blend設定
	D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = blendDesc.RenderTarget[0];
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	blenddesc.BlendEnable = true;
	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;
	blenddesc.BlendOp = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
	blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
	//Rasterrizer設定
	rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;

	//深度設定
	despthStencilDesc.DepthEnable = true;
	despthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
	despthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;

	//本体の作成
	graphicsPipelineStateDesc.pRootSignature = pso.rootSignature.Get();
	graphicsPipelineStateDesc.InputLayout = inputLayoutDesc;
	graphicsPipelineStateDesc.VS = {
		.pShaderBytecode = shader.vertexBlob->GetBufferPointer(),
		.BytecodeLength = shader.vertexBlob->GetBufferSize() };
	graphicsPipelineStateDesc.PS = {
		.pShaderBytecode = shader.pixelBlob->GetBufferPointer(),
		.BytecodeLength = shader.pixelBlob->GetBufferSize() };
	graphicsPipelineStateDesc.BlendState = blendDesc;
	graphicsPipelineStateDesc.RasterizerState = rasterizerDesc;
	graphicsPipelineStateDesc.DepthStencilState = despthStencilDesc;
	graphicsPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

	graphicsPipelineStateDesc.NumRenderTargets = 1;
	graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	graphicsPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	graphicsPipelineStateDesc.SampleDesc.Count = 1;
	graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

	hr = device->CreateGraphicsPipelineState(&graphicsPipelineStateDesc,
		IID_PPV_ARGS(&pso.GraphicsPipelineState));
	assert(SUCCEEDED(hr));

	return pso;
}

SPSOProperty CreateGpuParticle::CreateGpuParticle_AddDraw(ComPtr<ID3D12Device> device, Commands commands, SShaderMode shader)
{

	SPSOProperty pso;
	HRESULT hr = {};

	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	D3D12_BLEND_DESC blendDesc{};
	D3D12_RASTERIZER_DESC rasterizerDesc{};
	D3D12_DEPTH_STENCIL_DESC despthStencilDesc{};

	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};

	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	//rootsignature作成
	descriptionRootSignature.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	D3D12_ROOT_PARAMETER rootParameters[5] = {};
	//u0 : VS param uav
	D3D12_DESCRIPTOR_RANGE descriptorRangeVS_UAV[1] = {};
	descriptorRangeVS_UAV[0].BaseShaderRegister = 0;
	descriptorRangeVS_UAV[0].NumDescriptors = 1;
	descriptorRangeVS_UAV[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	descriptorRangeVS_UAV[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rootParameters[0].DescriptorTable.pDescriptorRanges = descriptorRangeVS_UAV;
	rootParameters[0].DescriptorTable.NumDescriptorRanges = _countof(descriptorRangeVS_UAV);

	//u1 : PS param uav
	D3D12_DESCRIPTOR_RANGE descriptorRangePS_UAV[1] = {};
	descriptorRangePS_UAV[0].BaseShaderRegister = 0;
	descriptorRangePS_UAV[0].NumDescriptors = 1;
	descriptorRangePS_UAV[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	descriptorRangePS_UAV[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[1].DescriptorTable.pDescriptorRanges = descriptorRangePS_UAV;
	rootParameters[1].DescriptorTable.NumDescriptorRanges = _countof(descriptorRangePS_UAV);

	//b0 : VSに送るカメラ

	rootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rootParameters[2].Descriptor.ShaderRegister = 0;

	//b0 : PSに送るカメラ
	rootParameters[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[3].Descriptor.ShaderRegister = 0;

	//テクスチャ
	D3D12_DESCRIPTOR_RANGE descriptorRangePS_Tex[1] = {};
	descriptorRangePS_Tex[0].BaseShaderRegister = 0;
	descriptorRangePS_Tex[0].NumDescriptors = 1;
	descriptorRangePS_Tex[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRangePS_Tex[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[4].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[4].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[4].DescriptorTable.pDescriptorRanges = descriptorRangePS_Tex;
	rootParameters[4].DescriptorTable.NumDescriptorRanges = _countof(descriptorRangePS_Tex);

	D3D12_STATIC_SAMPLER_DESC staticSamplers[1] = {};
	//Sampler
	staticSamplers[0].Filter = D3D12_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	staticSamplers[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;

	staticSamplers[0].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	staticSamplers[0].MaxLOD = D3D12_FLOAT32_MAX;
	staticSamplers[0].ShaderRegister = 0;
	staticSamplers[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;


	descriptionRootSignature.pParameters = rootParameters;
	descriptionRootSignature.NumParameters = _countof(rootParameters);

	descriptionRootSignature.pStaticSamplers = staticSamplers;
	descriptionRootSignature.NumStaticSamplers = _countof(staticSamplers);
	ComPtr<ID3DBlob> signatureBlob = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;
	hr = D3D12SerializeRootSignature(&descriptionRootSignature,
		D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
	if (FAILED(hr))
	{
		LogManager::Log(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
		assert(false);
	}
	hr = device->CreateRootSignature(0, signatureBlob->GetBufferPointer(),
		signatureBlob->GetBufferSize(), IID_PPV_ARGS(&pso.rootSignature));
	assert(SUCCEEDED(hr));

	//InputLayOut作成
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[4] = {};
	//pos
	inputElementDescs[0].SemanticName = "POSITION";
	inputElementDescs[0].SemanticIndex = 0;
	inputElementDescs[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	inputElementDescs[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

	//texCoord
	inputElementDescs[1].SemanticName = "TEXCOORD";
	inputElementDescs[1].SemanticIndex = 0;
	inputElementDescs[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	inputElementDescs[1].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

	//normal
	inputElementDescs[2].SemanticName = "NORMAL";
	inputElementDescs[2].SemanticIndex = 0;
	inputElementDescs[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	inputElementDescs[2].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

	//instancedId
	inputElementDescs[3].SemanticName = "INSTANCEID";
	inputElementDescs[3].SemanticIndex = 0;
	inputElementDescs[3].Format = DXGI_FORMAT_R32_UINT;
	inputElementDescs[3].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;


	inputLayoutDesc.pInputElementDescs = inputElementDescs;
	inputLayoutDesc.NumElements = _countof(inputElementDescs);

	//Blend設定
	D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = blendDesc.RenderTarget[0];
	CreateGraphicsPiplineFanc::SettingBlendState(blenddesc, BlendAdd);

	//Rasterrizer設定
	rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;

	//深度設定
	despthStencilDesc.DepthEnable = true;
	despthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
	despthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;

	//本体の作成
	graphicsPipelineStateDesc.pRootSignature = pso.rootSignature.Get();
	graphicsPipelineStateDesc.InputLayout = inputLayoutDesc;
	graphicsPipelineStateDesc.VS = {
		.pShaderBytecode = shader.vertexBlob->GetBufferPointer(),
		.BytecodeLength = shader.vertexBlob->GetBufferSize() };
	graphicsPipelineStateDesc.PS = {
		.pShaderBytecode = shader.pixelBlob->GetBufferPointer(),
		.BytecodeLength = shader.pixelBlob->GetBufferSize() };
	graphicsPipelineStateDesc.BlendState = blendDesc;
	graphicsPipelineStateDesc.RasterizerState = rasterizerDesc;
	graphicsPipelineStateDesc.DepthStencilState = despthStencilDesc;
	graphicsPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

	graphicsPipelineStateDesc.NumRenderTargets = 1;
	graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	graphicsPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	graphicsPipelineStateDesc.SampleDesc.Count = 1;
	graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

	hr = device->CreateGraphicsPipelineState(&graphicsPipelineStateDesc,
		IID_PPV_ARGS(&pso.GraphicsPipelineState));
	assert(SUCCEEDED(hr));

	return pso;
}

SPSOProperty CreateGpuParticle::CreateGpuParticle_DissolveNoneDraw(ComPtr<ID3D12Device> device, Commands commands, SShaderMode shader)
{

	SPSOProperty pso;
	HRESULT hr = {};

	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	D3D12_BLEND_DESC blendDesc{};
	D3D12_RASTERIZER_DESC rasterizerDesc{};
	D3D12_DEPTH_STENCIL_DESC despthStencilDesc{};
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};

	//rootsignature作成
	descriptionRootSignature.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	D3D12_ROOT_PARAMETER rootParameters[7] = {};
	//u0 : VS param uav
	D3D12_DESCRIPTOR_RANGE descriptorRangeVS_UAV[1] = {};
	descriptorRangeVS_UAV[0].BaseShaderRegister = 0;
	descriptorRangeVS_UAV[0].NumDescriptors = 1;
	descriptorRangeVS_UAV[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	descriptorRangeVS_UAV[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rootParameters[0].DescriptorTable.pDescriptorRanges = descriptorRangeVS_UAV;
	rootParameters[0].DescriptorTable.NumDescriptorRanges = _countof(descriptorRangeVS_UAV);

	//u1 : PS param uav
	D3D12_DESCRIPTOR_RANGE descriptorRangePS_UAV[1] = {};
	descriptorRangePS_UAV[0].BaseShaderRegister = 0;
	descriptorRangePS_UAV[0].NumDescriptors = 1;
	descriptorRangePS_UAV[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	descriptorRangePS_UAV[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[1].DescriptorTable.pDescriptorRanges = descriptorRangePS_UAV;
	rootParameters[1].DescriptorTable.NumDescriptorRanges = _countof(descriptorRangePS_UAV);

	//b0 : VSに送るカメラ

	rootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rootParameters[2].Descriptor.ShaderRegister = 0;

	//b0 : PSに送るカメラ
	rootParameters[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[3].Descriptor.ShaderRegister = 0;

	//テクスチャ
	D3D12_DESCRIPTOR_RANGE descriptorRangePS_Tex[1] = {};
	descriptorRangePS_Tex[0].BaseShaderRegister = 0;
	descriptorRangePS_Tex[0].NumDescriptors = 1;
	descriptorRangePS_Tex[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRangePS_Tex[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[4].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[4].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[4].DescriptorTable.pDescriptorRanges = descriptorRangePS_Tex;
	rootParameters[4].DescriptorTable.NumDescriptorRanges = _countof(descriptorRangePS_Tex);

	//テクスチャ
	D3D12_DESCRIPTOR_RANGE descriptorRangePS_noiseTex[1] = {};
	descriptorRangePS_noiseTex[0].BaseShaderRegister = 1;
	descriptorRangePS_noiseTex[0].NumDescriptors = 1;
	descriptorRangePS_noiseTex[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRangePS_noiseTex[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[5].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[5].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[5].DescriptorTable.pDescriptorRanges = descriptorRangePS_noiseTex;
	rootParameters[5].DescriptorTable.NumDescriptorRanges = _countof(descriptorRangePS_noiseTex);
	//b1 : PSに送るパラメーター
	rootParameters[6].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[6].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[6].Descriptor.ShaderRegister = 1;

	D3D12_STATIC_SAMPLER_DESC staticSamplers[1] = {};
	//Sampler
	staticSamplers[0].Filter = D3D12_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	staticSamplers[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;

	staticSamplers[0].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	staticSamplers[0].MaxLOD = D3D12_FLOAT32_MAX;
	staticSamplers[0].ShaderRegister = 0;
	staticSamplers[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;


	descriptionRootSignature.pParameters = rootParameters;
	descriptionRootSignature.NumParameters = _countof(rootParameters);

	descriptionRootSignature.pStaticSamplers = staticSamplers;
	descriptionRootSignature.NumStaticSamplers = _countof(staticSamplers);
	ComPtr<ID3DBlob> signatureBlob = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;
	hr = D3D12SerializeRootSignature(&descriptionRootSignature,
		D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
	if (FAILED(hr))
	{
		LogManager::Log(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
		assert(false);
	}
	hr = device->CreateRootSignature(0, signatureBlob->GetBufferPointer(),
		signatureBlob->GetBufferSize(), IID_PPV_ARGS(&pso.rootSignature));
	assert(SUCCEEDED(hr));

	//InputLayOut作成
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[4] = {};
	//pos
	inputElementDescs[0].SemanticName = "POSITION";
	inputElementDescs[0].SemanticIndex = 0;
	inputElementDescs[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	inputElementDescs[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

	//texCoord
	inputElementDescs[1].SemanticName = "TEXCOORD";
	inputElementDescs[1].SemanticIndex = 0;
	inputElementDescs[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	inputElementDescs[1].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

	//normal
	inputElementDescs[2].SemanticName = "NORMAL";
	inputElementDescs[2].SemanticIndex = 0;
	inputElementDescs[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	inputElementDescs[2].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

	//instancedId
	inputElementDescs[3].SemanticName = "INSTANCEID";
	inputElementDescs[3].SemanticIndex = 0;
	inputElementDescs[3].Format = DXGI_FORMAT_R32_UINT;
	inputElementDescs[3].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;


	inputLayoutDesc.pInputElementDescs = inputElementDescs;
	inputLayoutDesc.NumElements = _countof(inputElementDescs);

	//Blend設定
	D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = blendDesc.RenderTarget[0];
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	blenddesc.BlendEnable = true;
	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;
	blenddesc.BlendOp = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
	blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
	//Rasterrizer設定
	rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;

	//深度設定
	despthStencilDesc.DepthEnable = true;
	despthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
	despthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;

	//本体の作成
	graphicsPipelineStateDesc.pRootSignature = pso.rootSignature.Get();
	graphicsPipelineStateDesc.InputLayout = inputLayoutDesc;
	graphicsPipelineStateDesc.VS = {
		.pShaderBytecode = shader.vertexBlob->GetBufferPointer(),
		.BytecodeLength = shader.vertexBlob->GetBufferSize() };
	graphicsPipelineStateDesc.PS = {
		.pShaderBytecode = shader.pixelBlob->GetBufferPointer(),
		.BytecodeLength = shader.pixelBlob->GetBufferSize() };
	graphicsPipelineStateDesc.BlendState = blendDesc;
	graphicsPipelineStateDesc.RasterizerState = rasterizerDesc;
	graphicsPipelineStateDesc.DepthStencilState = despthStencilDesc;
	graphicsPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

	graphicsPipelineStateDesc.NumRenderTargets = 1;
	graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	graphicsPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	graphicsPipelineStateDesc.SampleDesc.Count = 1;
	graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

	hr = device->CreateGraphicsPipelineState(&graphicsPipelineStateDesc,
		IID_PPV_ARGS(&pso.GraphicsPipelineState));
	assert(SUCCEEDED(hr));

	return pso;
}

SPSOProperty CreateGpuParticle::CreateGpuParticle_Update(ComPtr<ID3D12Device> device, Commands commands, SShaderMode shader)
{
	SPSOProperty pso = {};

	D3D12_COMPUTE_PIPELINE_STATE_DESC psoDesc = {};
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	HRESULT hr = {};
	//rootsignature作成
	descriptionRootSignature.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	D3D12_ROOT_PARAMETER rootParameters[3] = {};

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

	//u1 : FreeListIndex
	D3D12_DESCRIPTOR_RANGE descriptorRange_FreeListIndex = {};
	descriptorRange_FreeListIndex.BaseShaderRegister = 1;
	descriptorRange_FreeListIndex.NumDescriptors = 1;
	descriptorRange_FreeListIndex.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	descriptorRange_FreeListIndex.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	rootParameters[1].DescriptorTable.pDescriptorRanges = &descriptorRange_FreeListIndex;
	rootParameters[1].DescriptorTable.NumDescriptorRanges = 1;

	//u2 : FreeList
	D3D12_DESCRIPTOR_RANGE descriptorRange_FreeList = {};
	descriptorRange_FreeList.BaseShaderRegister = 2;
	descriptorRange_FreeList.NumDescriptors = 1;
	descriptorRange_FreeList.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	descriptorRange_FreeList.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	rootParameters[2].DescriptorTable.pDescriptorRanges = &descriptorRange_FreeList;
	rootParameters[2].DescriptorTable.NumDescriptorRanges = 1;

	descriptionRootSignature.pParameters = rootParameters;
	descriptionRootSignature.NumParameters = _countof(rootParameters);
	//rootsignatureの作成
	ComPtr<ID3DBlob> signatureBlob = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;
	assert(shader.csBlob != nullptr);
	hr = D3D12SerializeRootSignature(&descriptionRootSignature,
		D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
	if (FAILED(hr))
	{
		LogManager::Log(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
		assert(false);
	}
	hr = device->CreateRootSignature(0, signatureBlob->GetBufferPointer(),
		signatureBlob->GetBufferSize(), IID_PPV_ARGS(&pso.rootSignature));
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

SPSOProperty CreateGpuParticle::CreateGpuParticcle_Emitter_Sphere(ComPtr<ID3D12Device> device, Commands commands, SShaderMode shader)
{

	SPSOProperty pso = {};

	D3D12_COMPUTE_PIPELINE_STATE_DESC psoDesc = {};
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	HRESULT hr = {};
	//rootsignature作成
	descriptionRootSignature.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	D3D12_ROOT_PARAMETER rootParameters[5] = {};

	//u0 : tパラメーターuav
	D3D12_DESCRIPTOR_RANGE descriptorRange_UAV = {};
	descriptorRange_UAV.BaseShaderRegister = 0;
	descriptorRange_UAV.NumDescriptors = 1;
	descriptorRange_UAV.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	descriptorRange_UAV.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	rootParameters[0].DescriptorTable.pDescriptorRanges = &descriptorRange_UAV;
	rootParameters[0].DescriptorTable.NumDescriptorRanges = 1;

	//t1 : tパラメーターsrv
	D3D12_DESCRIPTOR_RANGE descriptorRange_SRV = {};
	descriptorRange_SRV.BaseShaderRegister = 0;
	descriptorRange_SRV.NumDescriptors = 1;
	descriptorRange_SRV.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange_SRV.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	rootParameters[1].DescriptorTable.pDescriptorRanges = &descriptorRange_SRV;
	rootParameters[1].DescriptorTable.NumDescriptorRanges = 1;

	//b0 : exe起動時間
	rootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	rootParameters[2].Descriptor.ShaderRegister = 0;

	//u1 freeListIndex
	D3D12_DESCRIPTOR_RANGE descriptorRange_freeListIndex = {};
	descriptorRange_freeListIndex.BaseShaderRegister = 1;
	descriptorRange_freeListIndex.NumDescriptors = 1;
	descriptorRange_freeListIndex.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	descriptorRange_freeListIndex.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	rootParameters[3].DescriptorTable.pDescriptorRanges = &descriptorRange_freeListIndex;
	rootParameters[3].DescriptorTable.NumDescriptorRanges = 1;

	//u2 freeList
	D3D12_DESCRIPTOR_RANGE descriptorRange_freeList = {};
	descriptorRange_freeList.BaseShaderRegister = 2;
	descriptorRange_freeList.NumDescriptors = 1;
	descriptorRange_freeList.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	descriptorRange_freeList.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[4].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[4].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	rootParameters[4].DescriptorTable.pDescriptorRanges = &descriptorRange_freeList;
	rootParameters[4].DescriptorTable.NumDescriptorRanges = 1;

	descriptionRootSignature.pParameters = rootParameters;
	descriptionRootSignature.NumParameters = _countof(rootParameters);
	ComPtr<ID3DBlob> signatureBlob = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;
	//rootsignatureの作成
	assert(shader.csBlob != nullptr);
	hr = D3D12SerializeRootSignature(&descriptionRootSignature,
		D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
	if (FAILED(hr))
	{
		LogManager::Log(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
		assert(false);
	}
	hr = device->CreateRootSignature(0, signatureBlob->GetBufferPointer(),
		signatureBlob->GetBufferSize(), IID_PPV_ARGS(&pso.rootSignature));
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

SPSOProperty CreateGpuParticle::CreateGpuParticcle_Emitter_Box(ComPtr<ID3D12Device> device, Commands commands, SShaderMode shader)
{

	SPSOProperty pso = {};

	D3D12_COMPUTE_PIPELINE_STATE_DESC psoDesc = {};
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	HRESULT hr = {};
	//rootsignature作成
	descriptionRootSignature.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	D3D12_ROOT_PARAMETER rootParameters[5] = {};

	//u0 : tパラメーターuav
	D3D12_DESCRIPTOR_RANGE descriptorRange_UAV = {};
	descriptorRange_UAV.BaseShaderRegister = 0;
	descriptorRange_UAV.NumDescriptors = 1;
	descriptorRange_UAV.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	descriptorRange_UAV.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	rootParameters[0].DescriptorTable.pDescriptorRanges = &descriptorRange_UAV;
	rootParameters[0].DescriptorTable.NumDescriptorRanges = 1;

	//t1 : tパラメーターsrv
	D3D12_DESCRIPTOR_RANGE descriptorRange_SRV = {};
	descriptorRange_SRV.BaseShaderRegister = 0;
	descriptorRange_SRV.NumDescriptors = 1;
	descriptorRange_SRV.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange_SRV.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	rootParameters[1].DescriptorTable.pDescriptorRanges = &descriptorRange_SRV;
	rootParameters[1].DescriptorTable.NumDescriptorRanges = 1;

	//b0 : exe起動時間
	rootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	rootParameters[2].Descriptor.ShaderRegister = 0;

	//u1 freeListIndex
	D3D12_DESCRIPTOR_RANGE descriptorRange_freeListIndex = {};
	descriptorRange_freeListIndex.BaseShaderRegister = 1;
	descriptorRange_freeListIndex.NumDescriptors = 1;
	descriptorRange_freeListIndex.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	descriptorRange_freeListIndex.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	rootParameters[3].DescriptorTable.pDescriptorRanges = &descriptorRange_freeListIndex;
	rootParameters[3].DescriptorTable.NumDescriptorRanges = 1;

	//u2 freeList
	D3D12_DESCRIPTOR_RANGE descriptorRange_freeList = {};
	descriptorRange_freeList.BaseShaderRegister = 2;
	descriptorRange_freeList.NumDescriptors = 1;
	descriptorRange_freeList.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	descriptorRange_freeList.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[4].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[4].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	rootParameters[4].DescriptorTable.pDescriptorRanges = &descriptorRange_freeList;
	rootParameters[4].DescriptorTable.NumDescriptorRanges = 1;

	descriptionRootSignature.pParameters = rootParameters;
	descriptionRootSignature.NumParameters = _countof(rootParameters);

	ComPtr<ID3DBlob> signatureBlob = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;
	//rootsignatureの作成
	assert(shader.csBlob != nullptr);
	hr = D3D12SerializeRootSignature(&descriptionRootSignature,
		D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
	if (FAILED(hr))
	{
		LogManager::Log(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
		assert(false);
	}
	hr = device->CreateRootSignature(0, signatureBlob->GetBufferPointer(),
		signatureBlob->GetBufferSize(), IID_PPV_ARGS(&pso.rootSignature));
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

SPSOProperty CreateGpuParticle::CreateGpuParticle_Field_Suction(ComPtr<ID3D12Device> device, Commands commands, SShaderMode shader)
{
	SPSOProperty pso = {};

	D3D12_COMPUTE_PIPELINE_STATE_DESC psoDesc = {};
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	HRESULT hr = {};
	//rootsignature作成
	descriptionRootSignature.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	D3D12_ROOT_PARAMETER rootParameters[2] = {};

	//u0 : tパラメーターuav
	D3D12_DESCRIPTOR_RANGE descriptorRange_UAV = {};
	descriptorRange_UAV.BaseShaderRegister = 0;
	descriptorRange_UAV.NumDescriptors = 1;
	descriptorRange_UAV.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	descriptorRange_UAV.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	rootParameters[0].DescriptorTable.pDescriptorRanges = &descriptorRange_UAV;
	rootParameters[0].DescriptorTable.NumDescriptorRanges = 1;

	//t1 : tパラメーターsrv
	D3D12_DESCRIPTOR_RANGE descriptorRange_SRV = {};
	descriptorRange_SRV.BaseShaderRegister = 0;
	descriptorRange_SRV.NumDescriptors = 1;
	descriptorRange_SRV.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange_SRV.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	rootParameters[1].DescriptorTable.pDescriptorRanges = &descriptorRange_SRV;
	rootParameters[1].DescriptorTable.NumDescriptorRanges = 1;


	descriptionRootSignature.pParameters = rootParameters;
	descriptionRootSignature.NumParameters = _countof(rootParameters);

	ComPtr<ID3DBlob> signatureBlob = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;
	//rootsignatureの作成
	assert(shader.csBlob != nullptr);
	hr = D3D12SerializeRootSignature(&descriptionRootSignature,
		D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
	if (FAILED(hr))
	{
		LogManager::Log(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
		assert(false);
	}
	hr = device->CreateRootSignature(0, signatureBlob->GetBufferPointer(),
		signatureBlob->GetBufferSize(), IID_PPV_ARGS(&pso.rootSignature));
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
