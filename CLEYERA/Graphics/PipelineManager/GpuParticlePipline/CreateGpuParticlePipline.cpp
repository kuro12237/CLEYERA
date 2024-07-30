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

SPSOProperty CreateGpuParticle::CreateGpuParticle_DebugDraw(ComPtr<ID3D12Device> device, Commands commands, SShaderMode shader)
{
	ComPtr<ID3DBlob> signatureBlob = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;
	SPSOProperty pso;
	HRESULT hr = {};

	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	D3D12_BLEND_DESC blendDesc{};
	D3D12_RASTERIZER_DESC rasterizerDesc{};
	D3D12_DEPTH_STENCIL_DESC despthStencilDesc{};
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};

	{//rootsignature作成
		descriptionRootSignature.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

		D3D12_ROOT_PARAMETER rootParameters[5] = {};
		{//u0 : VS param uav
			D3D12_DESCRIPTOR_RANGE descriptorRange = {};
			descriptorRange.BaseShaderRegister = 0;
			descriptorRange.NumDescriptors = 1;
			descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
			descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

			rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
			rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
			rootParameters[0].DescriptorTable.pDescriptorRanges = &descriptorRange;
			rootParameters[0].DescriptorTable.NumDescriptorRanges = 1;
		}
		{//u1 : PS param uav
			D3D12_DESCRIPTOR_RANGE descriptorRange = {};
			descriptorRange.BaseShaderRegister = 1;
			descriptorRange.NumDescriptors = 1;
			descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
			descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

			rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
			rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
			rootParameters[1].DescriptorTable.pDescriptorRanges = &descriptorRange;
			rootParameters[1].DescriptorTable.NumDescriptorRanges = 1;
		}
		{//b0 : VSに送るカメラ

			rootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
			rootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
			rootParameters[2].Descriptor.ShaderRegister = 0;
		}
		{//b0 : PSに送るカメラ
			rootParameters[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
			rootParameters[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
			rootParameters[3].Descriptor.ShaderRegister = 0;
		}
		{//テクスチャ
			D3D12_DESCRIPTOR_RANGE descriptorRange[1] = {};
			descriptorRange[0].BaseShaderRegister = 0;
			descriptorRange[0].NumDescriptors = 1;
			descriptorRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
			descriptorRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

			rootParameters[4].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
			rootParameters[4].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
			rootParameters[4].DescriptorTable.pDescriptorRanges = descriptorRange;
			rootParameters[4].DescriptorTable.NumDescriptorRanges = _countof(descriptorRange);
		}
		D3D12_STATIC_SAMPLER_DESC staticSamplers[1] = {};
		{//Sampler
			staticSamplers[0].Filter = D3D12_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
			staticSamplers[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			staticSamplers[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			staticSamplers[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;

			staticSamplers[0].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
			staticSamplers[0].MaxLOD = D3D12_FLOAT32_MAX;
			staticSamplers[0].ShaderRegister = 0;
			staticSamplers[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
		}

		descriptionRootSignature.pParameters = rootParameters;
		descriptionRootSignature.NumParameters = _countof(rootParameters);

		descriptionRootSignature.pStaticSamplers = staticSamplers;
		descriptionRootSignature.NumStaticSamplers = _countof(staticSamplers);

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
	}
	{//InputLayOut作成
		D3D12_INPUT_ELEMENT_DESC inputElementDescs[4] = {};
		{//pos
			inputElementDescs[0].SemanticName = "POSITION";
			inputElementDescs[0].SemanticIndex = 0;
			inputElementDescs[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			inputElementDescs[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
		}
		{//texCoord
			inputElementDescs[1].SemanticName = "TEXCOORD";
			inputElementDescs[1].SemanticIndex = 0;
			inputElementDescs[1].Format = DXGI_FORMAT_R32G32_FLOAT;
			inputElementDescs[1].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
		}
		{//normal
			inputElementDescs[2].SemanticName = "NORMAL";
			inputElementDescs[2].SemanticIndex = 0;
			inputElementDescs[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
			inputElementDescs[2].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
		}
		{//worPos
			inputElementDescs[3].SemanticName = "WORLDPOSITION";
			inputElementDescs[3].SemanticIndex = 0;
			inputElementDescs[3].Format = DXGI_FORMAT_R32G32B32_FLOAT;
			inputElementDescs[3].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
		}

		inputLayoutDesc.pInputElementDescs = inputElementDescs;
		inputLayoutDesc.NumElements = _countof(inputElementDescs);
	}
	{//Blend設定
		blendDesc.RenderTarget[0].RenderTargetWriteMask =
			D3D12_COLOR_WRITE_ENABLE_ALL;
	}
	{//Rasterrizer設定
		rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
		rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
	}
	{//深度設定
		despthStencilDesc.DepthEnable = true;
		despthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
		despthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
	}
	{//本体の作成
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
		graphicsPipelineStateDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;

		graphicsPipelineStateDesc.NumRenderTargets = 4;
		graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		graphicsPipelineStateDesc.RTVFormats[1] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		graphicsPipelineStateDesc.RTVFormats[2] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		graphicsPipelineStateDesc.RTVFormats[3] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		graphicsPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		graphicsPipelineStateDesc.SampleDesc.Count = 1;
		graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

		hr = device->CreateGraphicsPipelineState(&graphicsPipelineStateDesc,
			IID_PPV_ARGS(&pso.GraphicsPipelineState));
		assert(SUCCEEDED(hr));
	}

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

SPSOProperty CreateGpuParticle::CreateGpuparticcle_Emitter_Sphere(ComPtr<ID3D12Device> device, Commands commands, SShaderMode shader)
{

	SPSOProperty pso = {};

	D3D12_COMPUTE_PIPELINE_STATE_DESC psoDesc = {};
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	HRESULT hr = {};
	//rootsignature作成
	descriptionRootSignature.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	D3D12_ROOT_PARAMETER rootParameters[3] = {};

	{//u0 : tパラメーターuav
		D3D12_DESCRIPTOR_RANGE descriptorRange = {};
		descriptorRange.BaseShaderRegister = 0;
		descriptorRange.NumDescriptors = 1;
		descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
		descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

		rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
		rootParameters[0].DescriptorTable.pDescriptorRanges = &descriptorRange;
		rootParameters[0].DescriptorTable.NumDescriptorRanges = 1;
	}
	{//t0 : tパラメーターuav
		D3D12_DESCRIPTOR_RANGE descriptorRange = {};
		descriptorRange.BaseShaderRegister = 0;
		descriptorRange.NumDescriptors = 1;
		descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
		descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

		rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
		rootParameters[1].DescriptorTable.pDescriptorRanges = &descriptorRange;
		rootParameters[1].DescriptorTable.NumDescriptorRanges = 1;
	}
	{//b0 : exe起動時間

		rootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
		rootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
		rootParameters[2].Descriptor.ShaderRegister = 0;
	}

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
