#include "GraphicsPipelineManager.h"

using namespace Pipline;
using namespace Engine::Base::DX;

GraphicsPipelineManager* GraphicsPipelineManager::GetInstance()
{
	static GraphicsPipelineManager instance;
	return &instance;
}

void GraphicsPipelineManager::Initialize()
{
	ComPtr<ID3D12Device5> device = DirectXCommon::GetInstance()->GetDevice();
	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	SShaders shader = ShaderManager::Getinstance()->GetShader();

	auto shaderInstance = ShaderManager::Getinstance();

	Sprite_2d_CreatePipline::GetInstance()->Initialize();
	piplines_[SPRITE_2d]["None"] = Sprite_2d_CreatePipline::GetInstance()->CreateNone(shaderInstance->GetShaders(Shader::SPRITE_2d, "None"));
	piplines_[SPRITE_2d]["Add"] = Sprite_2d_CreatePipline::GetInstance()->CreateAdd(shaderInstance->GetShaders(Shader::SPRITE_2d, "None"));
	piplines_[SPRITE_2d]["Subtract"] = Sprite_2d_CreatePipline::GetInstance()->CreateSubtract(shaderInstance->GetShaders(Shader::SPRITE_2d, "None"));
	piplines_[SPRITE_2d]["Multiply"] = Sprite_2d_CreatePipline::GetInstance()->CreateMultiply(shaderInstance->GetShaders(Shader::SPRITE_2d, "None"));
	piplines_[SPRITE_2d]["Screen"] = Sprite_2d_CreatePipline::GetInstance()->CreateScreen(shaderInstance->GetShaders(Shader::SPRITE_2d, "None"));
	piplines_[SPRITE_2d]["DissolveNone"] = Sprite_2d_CreatePipline::GetInstance()->CreateDissolveNone(shaderInstance->GetShaders(Shader::SPRITE_2d, "Dissolve"));
	piplines_[SPRITE_2d]["PerlinNoise"] = Sprite_2d_CreatePipline::GetInstance()->CreatePerlinNoise(shaderInstance->GetShaders(Shader::SPRITE_2d, "PerlinNoise"));
	LogManager::CompliteLog("Sprite2dPSO");

	//3d
	piplines_[NONE_3d]["None"] = CreateShape(device.Get(), commands, shader.shape);
	piplines_[SPRITE_3d]["None"] = CreateSprite3dNone(device.Get(), commands, shader.sprite3d);
	piplines_[SPRITE_3d]["AddNoneWriteDepth"] = CreateSprite3dAddNoneWriteDepth(device.Get(), commands, shader.sprite3d);

	piplines_[LINE_3d]["None"] = CreateLine(device.Get(), commands, shader.Line);
	piplines_[SKYBOX]["None"] = ModelCreatePipline::CreateSkyBoxModel(device, commands, shader.SkyBoxModel);

	Phong_CreatePipline::GetInstance()->Initialize();
	piplines_[PHONG]["None"] = Phong_CreatePipline::GetInstance()->CreatePhongNormalModel(shader.Phong_Normal_Model);
	piplines_[PHONG]["Instancing_None"] = Phong_CreatePipline::GetInstance()->CreateInstancingModel(shader.Phong_Normal_InstancingModel);
	piplines_[PHONG]["Subsurface"] = Phong_CreatePipline::GetInstance()->CreateSubsurfaceModel(shader.Phong_subsurface_Model);
	piplines_[PHONG]["Skinning_None"] = Phong_CreatePipline::GetInstance()->CreateSkinningModel(shader.skinningPhongModel);
	piplines_[PHONG]["Skinning_NoneDepthWrite"] = Phong_CreatePipline::GetInstance()->CreateSkinningModel(shader.skinningPhongModel, true);
	
	//PBR
	piplines_[PBR]["None"] = Phong_CreatePipline::GetInstance()->CreatePhongNormalModel(ShaderManager::Getinstance()->GetShaders(Shader::PBR,"None"));
	//piplines_[PBR]["Skinning_None"] = Phong_CreatePipline::GetInstance()->CreateSkinningModel(ShaderManager::Getinstance()->GetShaders(Shader::PBR, "Skinning_None"));

	D3D12_RASTERIZER_DESC dissolveRasterRizer{};
	dissolveRasterRizer.CullMode = D3D12_CULL_MODE_NONE;
	dissolveRasterRizer.FillMode = D3D12_FILL_MODE_SOLID;

	piplines_[PHONG]["Dissolve"] = Phong_CreatePipline::GetInstance()->CreateDissolveNormalModel(shader.Phong_Dissolve_Model, dissolveRasterRizer);
	dissolveRasterRizer.CullMode = D3D12_CULL_MODE_NONE;
	piplines_[PHONG]["Dissolve_FrontBackWrite"] = Phong_CreatePipline::GetInstance()->CreateDissolveNormalModel(shader.Phong_Dissolve_Model,dissolveRasterRizer);

	//PostEffect
	piplines_[POST_EFFECT]["None"] = CreatePostEffectTest(device, commands, shader.PostEffect);

	//Particle
	GpuParticleShader  shaderParticle = ShaderManager::Getinstance()->GetParticleShader();

	piplines_[PARTICLE_INIT]["None"] = CreateGpuParticle::CreateGpuParticle_Init(device, commands, shaderParticle.particleInit);

	piplines_[PARTICLE_UPDATE]["None"] = CreateGpuParticle::CreateGpuParticle_Update(device, commands, shaderParticle.particleUpdate);

	piplines_[PARTICLE_EMITTER]["Sphere"] = CreateGpuParticle::CreateGpuParticcle_Emitter_Sphere(device, commands, shaderParticle.particleSphereEmitter);
	piplines_[PARTICLE_EMITTER]["Box"] = CreateGpuParticle::CreateGpuParticcle_Emitter_Box(device, commands, shaderInstance->GetShaders(Shader::PARTICLE_EMITTER,"Box"));
	piplines_[PARTICLE_EMITTER]["Goal"] = CreateGpuParticle::CreateGpuParticcle_Emitter_Box(device, commands, shaderInstance->GetShaders(Shader::PARTICLE_EMITTER, "Goal"));

	piplines_[PARTICLE_FIELD]["Suction"] = CreateGpuParticle::CreateGpuParticle_Field_Suction(device, commands, shaderInstance->GetShaders(Shader::PARTICLE_FIELD, "Suction"));
	piplines_[PARTICLE_FIELD]["Gravity"] = CreateGpuParticle::CreateGpuParticle_Field_Suction(device, commands, shaderInstance->GetShaders(Shader::PARTICLE_FIELD, "Gravity"));
	piplines_[PARTICLE_FIELD]["HitBox"] = CreateGpuParticle::CreateGpuParticle_Field_Suction(device, commands, shaderInstance->GetShaders(Shader::PARTICLE_FIELD, "HitBox"));


	piplines_[PARTICLE_DRAW]["None3d"] = CreateGpuParticle::CreateGpuParticle_NoneDraw(device, commands, shaderInstance->GetShaders(Shader::PARTICLE_DRAW, "None3d"));
	piplines_[PARTICLE_DRAW]["Add3d"] = CreateGpuParticle::CreateGpuParticle_AddDraw(device, commands, shaderInstance->GetShaders(Shader::PARTICLE_DRAW, "None3d"));
	piplines_[PARTICLE_DRAW]["None2d"] = CreateGpuParticle::CreateGpuParticle_NoneDraw(device, commands, shaderInstance->GetShaders(Shader::PARTICLE_DRAW, "None2d"));
	piplines_[PARTICLE_DRAW]["Add2d"] = CreateGpuParticle::CreateGpuParticle_AddDraw(device, commands, shaderInstance->GetShaders(Shader::PARTICLE_DRAW, "None2d"));
	piplines_[PARTICLE_DRAW]["DissolveNone2d"] = CreateGpuParticle::CreateGpuParticle_DissolveNoneDraw(device, commands, shaderInstance->GetShaders(Shader::PARTICLE_DRAW, "DissolveNone2d"));


}

SPSOProperty GraphicsPipelineManager::CreateShape(ComPtr<ID3D12Device> device, Commands command, SShaderMode shader)
{
	SPSOProperty result;
	//RootSignature�쐬
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};

	descriptionRootSignature.Flags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	//Material�ݒ�
	D3D12_ROOT_PARAMETER rootParameters[3] = {};
	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[0].Descriptor.ShaderRegister = 0;
	//Vertex��Transform
	rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rootParameters[1].Descriptor.ShaderRegister = 0;

	rootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rootParameters[2].Descriptor.ShaderRegister = 1;


	descriptionRootSignature.pParameters = rootParameters;
	descriptionRootSignature.NumParameters = _countof(rootParameters);

	//RootSignature�̍쐬
	CreateGraphicsPiplineFanc::CreateRootSignature(
		device,
		descriptionRootSignature,
		result
	);

	//InputLayout�̐ݒ�
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[1] = {};
	CreateGraphicsPiplineFanc::SettingInputElementDesc(
		inputElementDescs[0],
		"POSITION",
		0,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		D3D12_APPEND_ALIGNED_ELEMENT
	);

	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	inputLayoutDesc.pInputElementDescs = inputElementDescs;
	inputLayoutDesc.NumElements = _countof(inputElementDescs);

	//BlendState�̐ݒ�
	D3D12_BLEND_DESC blendDesc{};
	D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = blendDesc.RenderTarget[0];
	CreateGraphicsPiplineFanc::SettingBlendState(blenddesc, BlendNone);

	//Rasterrizer�ݒ�
	D3D12_RASTERIZER_DESC rasterizerDesc{};
	CreateGraphicsPiplineFanc::SettingRasterizer(
		rasterizerDesc,
		D3D12_CULL_MODE_FRONT,
		D3D12_FILL_MODE_SOLID
	);
	//�[�x
	D3D12_DEPTH_STENCIL_DESC despthStencilDesc{};
	CreateGraphicsPiplineFanc::SettingDepth(
		despthStencilDesc,
		true,
		D3D12_DEPTH_WRITE_MASK_ALL,
		D3D12_COMPARISON_FUNC_LESS_EQUAL
	);

	//PSO�̐���
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};

	graphicsPipelineStateDesc.pRootSignature = result.rootSignature.Get(); //RootSignature
	graphicsPipelineStateDesc.InputLayout = inputLayoutDesc; //InputLayout
	graphicsPipelineStateDesc.VS = { shader.vertexBlob->GetBufferPointer(),
	shader.vertexBlob->GetBufferSize() }; //VertexShader
	graphicsPipelineStateDesc.PS = { shader.pixelBlob->GetBufferPointer(),
	shader.pixelBlob->GetBufferSize() }; //PixeShader
	graphicsPipelineStateDesc.BlendState = blendDesc; //BlendState
	graphicsPipelineStateDesc.RasterizerState = rasterizerDesc; //RasterizerState

	graphicsPipelineStateDesc.DepthStencilState = despthStencilDesc;
	graphicsPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

	//��������RTV�̏��
	graphicsPipelineStateDesc.NumRenderTargets = 1;
	graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;

	//���p����g�|���W(�`��)�̃^�C�v�B�O�p�`
	graphicsPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	//�ǂ̂悤�ɉ�ʂɐF��ł����ނ��̐ݒ�(�C�ɂ��Ȃ��ėǂ�)
	graphicsPipelineStateDesc.SampleDesc.Count = 1;
	graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

	HRESULT hr = {};
	hr = device->CreateGraphicsPipelineState(&graphicsPipelineStateDesc,
		IID_PPV_ARGS(&result.GraphicsPipelineState));
	assert(SUCCEEDED(hr));

	return result;
}

SPSOProperty GraphicsPipelineManager::CreateLine(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader)
{
	SPSOProperty result;

	//RootSignature
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	descriptionRootSignature.Flags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	//Material
	D3D12_ROOT_PARAMETER rootParameters[4] = {};
	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[0].Descriptor.ShaderRegister = 0;
	//カメラ
	rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rootParameters[1].Descriptor.ShaderRegister = 1;

	//行列
	rootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rootParameters[2].Descriptor.ShaderRegister = 2;

	//texDescriptorRanged
	D3D12_DESCRIPTOR_RANGE descriptorRangeVertices[1] = {};
	descriptorRangeVertices[0].BaseShaderRegister = 0;
	descriptorRangeVertices[0].NumDescriptors = 1;
	descriptorRangeVertices[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRangeVertices[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	//tex
	rootParameters[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rootParameters[3].DescriptorTable.pDescriptorRanges = descriptorRangeVertices;
	rootParameters[3].DescriptorTable.NumDescriptorRanges = _countof(descriptorRangeVertices);

	descriptionRootSignature.pParameters = rootParameters;
	descriptionRootSignature.NumParameters = _countof(rootParameters);

	//RootSignature
	CreateGraphicsPiplineFanc::CreateRootSignature(
		device,
		descriptionRootSignature,
		result
	);

	//InputLayout
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[1] = {};
	CreateGraphicsPiplineFanc::SettingInputElementDesc(inputElementDescs[0],
		"POSITION",
		0,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		D3D12_APPEND_ALIGNED_ELEMENT
	);

	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	inputLayoutDesc.pInputElementDescs = inputElementDescs;
	inputLayoutDesc.NumElements = _countof(inputElementDescs);

	//BlendState�̐ݒ�
	D3D12_BLEND_DESC blendDesc{};
	D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = blendDesc.RenderTarget[0];
	CreateGraphicsPiplineFanc::SettingBlendState(
		blenddesc,
		BlendNone
	);

	//Rasterrizer�ݒ�
	D3D12_RASTERIZER_DESC rasterizerDesc{};
	CreateGraphicsPiplineFanc::SettingRasterizer(
		rasterizerDesc,
		D3D12_CULL_MODE_FRONT,
		D3D12_FILL_MODE_SOLID
	);

	//�[�x�ݒ�
	D3D12_DEPTH_STENCIL_DESC despthStencilDesc{};
	CreateGraphicsPiplineFanc::SettingDepth(
		despthStencilDesc,
		true,
		D3D12_DEPTH_WRITE_MASK_ALL,
		D3D12_COMPARISON_FUNC_LESS_EQUAL
	);

	//PSO�̐���
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};

	graphicsPipelineStateDesc.pRootSignature = result.rootSignature.Get(); //RootSignature
	graphicsPipelineStateDesc.InputLayout = inputLayoutDesc; //InputLayout
	graphicsPipelineStateDesc.VS = { shader.vertexBlob->GetBufferPointer(),
	shader.vertexBlob->GetBufferSize() }; //VertexShader
	graphicsPipelineStateDesc.PS = { shader.pixelBlob->GetBufferPointer(),
	shader.pixelBlob->GetBufferSize() }; //PixeShader
	graphicsPipelineStateDesc.BlendState = blendDesc; //BlendState
	graphicsPipelineStateDesc.RasterizerState = rasterizerDesc; //RasterizerState

	graphicsPipelineStateDesc.DepthStencilState = despthStencilDesc;
	graphicsPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

	//��������RTV�̏��
	graphicsPipelineStateDesc.NumRenderTargets = 1;
	graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;

	//���p����g�|���W(�`��)�̃^�C�v�B�O�p�`
	graphicsPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;

	//�ǂ̂悤�ɉ�ʂɐF��ł����ނ��̐ݒ�(�C�ɂ��Ȃ��ėǂ�)
	graphicsPipelineStateDesc.SampleDesc.Count = 1;
	graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

	HRESULT hr = {};
	hr = device->CreateGraphicsPipelineState(&graphicsPipelineStateDesc,
		IID_PPV_ARGS(&result.GraphicsPipelineState));
	assert(SUCCEEDED(hr));
	return result;
}

SPSOProperty GraphicsPipelineManager::CreateSprite3dNone(ComPtr<ID3D12Device> device, Commands commands, SShaderMode shader)
{
	SPSOProperty SpritePSO;

	//RootSignature
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	descriptionRootSignature.Flags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;


	D3D12_ROOT_PARAMETER rootParameters[7] = {};

	//Material
	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[0].Descriptor.ShaderRegister = 0;
	//worldTransform
	rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rootParameters[1].Descriptor.ShaderRegister = 0;
	//view行列
	rootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rootParameters[2].Descriptor.ShaderRegister = 1;
	//view行列
	rootParameters[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[3].Descriptor.ShaderRegister = 2;
	//LightData
	D3D12_DESCRIPTOR_RANGE descriptorRangeForInstancing[1] = {};
	descriptorRangeForInstancing[0].BaseShaderRegister = 0;
	descriptorRangeForInstancing[0].NumDescriptors = 1;
	descriptorRangeForInstancing[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRangeForInstancing[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[4].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[4].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[4].DescriptorTable.pDescriptorRanges = descriptorRangeForInstancing;
	rootParameters[4].DescriptorTable.NumDescriptorRanges = _countof(descriptorRangeForInstancing);

	//今のLightの個数
	rootParameters[5].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[5].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[5].Descriptor.ShaderRegister = 4;

	//texDescriptorRanged
	D3D12_DESCRIPTOR_RANGE descriptorRange[1] = {};
	descriptorRange[0].BaseShaderRegister = 1;
	descriptorRange[0].NumDescriptors = 1;
	descriptorRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	//tex
	rootParameters[6].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[6].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[6].DescriptorTable.pDescriptorRanges = descriptorRange;
	rootParameters[6].DescriptorTable.NumDescriptorRanges = _countof(descriptorRange);



	//Sampler
	D3D12_STATIC_SAMPLER_DESC staticSamplers[1] = {};
	staticSamplers[0].Filter = D3D12_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	staticSamplers[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;

	staticSamplers[0].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	staticSamplers[0].MaxLOD = D3D12_FLOAT32_MAX;
	staticSamplers[0].ShaderRegister = 0;
	staticSamplers[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	descriptionRootSignature.pStaticSamplers = staticSamplers;
	descriptionRootSignature.NumStaticSamplers = _countof(staticSamplers);

	descriptionRootSignature.pParameters = rootParameters;
	descriptionRootSignature.NumParameters = _countof(rootParameters);

	//RootSignature�쐬
	CreateGraphicsPiplineFanc::CreateRootSignature(
		device, descriptionRootSignature, SpritePSO);

	//InputLayout�̐ݒ�
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[2] = {};
	//Position
	CreateGraphicsPiplineFanc::SettingInputElementDesc(
		inputElementDescs[0],
		"POSITION",
		0,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		D3D12_APPEND_ALIGNED_ELEMENT
	);
	//Texcoord
	CreateGraphicsPiplineFanc::SettingInputElementDesc(
		inputElementDescs[1],
		"TEXCOORD",
		0,
		DXGI_FORMAT_R32G32_FLOAT,
		D3D12_APPEND_ALIGNED_ELEMENT
	);

	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	inputLayoutDesc.pInputElementDescs = inputElementDescs;
	inputLayoutDesc.NumElements = _countof(inputElementDescs);

	//BlendState
	D3D12_BLEND_DESC blendDesc{};
	D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = blendDesc.RenderTarget[0];
	CreateGraphicsPiplineFanc::SettingBlendState(blenddesc, BlendNone);

	//RasterrizerState�ڐݒ�
	D3D12_RASTERIZER_DESC rasterizerDesc{};
	CreateGraphicsPiplineFanc::SettingRasterizer(
		rasterizerDesc,
		D3D12_CULL_MODE_BACK,
		D3D12_FILL_MODE_SOLID
	);


	D3D12_DEPTH_STENCIL_DESC despthStencilDesc{};
	CreateGraphicsPiplineFanc::SettingDepth(
		despthStencilDesc,
		true,
		D3D12_DEPTH_WRITE_MASK_ALL,
		D3D12_COMPARISON_FUNC_LESS_EQUAL
	);


	//PSO作成
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};

	graphicsPipelineStateDesc.pRootSignature = SpritePSO.rootSignature.Get(); //RootSignature
	graphicsPipelineStateDesc.InputLayout = inputLayoutDesc; //InputLayout
	graphicsPipelineStateDesc.VS = { shader.vertexBlob->GetBufferPointer(),
	shader.vertexBlob->GetBufferSize() }; //VertexShader
	graphicsPipelineStateDesc.PS = { shader.pixelBlob->GetBufferPointer(),
	shader.pixelBlob->GetBufferSize() }; //PixeShader
	graphicsPipelineStateDesc.BlendState = blendDesc; //BlendState
	graphicsPipelineStateDesc.RasterizerState = rasterizerDesc; //RasterizerState
	graphicsPipelineStateDesc.DepthStencilState = despthStencilDesc;
	graphicsPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;


	graphicsPipelineStateDesc.NumRenderTargets = 1;
	graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;


	graphicsPipelineStateDesc.PrimitiveTopologyType =
		D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	graphicsPipelineStateDesc.SampleDesc.Count = 1;
	graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

	HRESULT hr = {};
	hr = device->CreateGraphicsPipelineState(&graphicsPipelineStateDesc,
		IID_PPV_ARGS(&SpritePSO.GraphicsPipelineState));
	assert(SUCCEEDED(hr));

	return SpritePSO;
}

SPSOProperty GraphicsPipelineManager::CreateSprite3dAddNoneWriteDepth(ComPtr<ID3D12Device> device, Commands commands, SShaderMode shader)
{
	SPSOProperty SpritePSO;

	//RootSignature
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	descriptionRootSignature.Flags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;


	D3D12_ROOT_PARAMETER rootParameters[7] = {};

	//Material
	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[0].Descriptor.ShaderRegister = 0;
	//worldTransform
	rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rootParameters[1].Descriptor.ShaderRegister = 0;
	//view行列
	rootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rootParameters[2].Descriptor.ShaderRegister = 1;
	//view行列
	rootParameters[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[3].Descriptor.ShaderRegister = 2;
	//LightData
	D3D12_DESCRIPTOR_RANGE descriptorRangeForInstancing[1] = {};
	descriptorRangeForInstancing[0].BaseShaderRegister = 0;
	descriptorRangeForInstancing[0].NumDescriptors = 1;
	descriptorRangeForInstancing[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRangeForInstancing[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[4].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[4].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[4].DescriptorTable.pDescriptorRanges = descriptorRangeForInstancing;
	rootParameters[4].DescriptorTable.NumDescriptorRanges = _countof(descriptorRangeForInstancing);

	//今のLightの個数
	rootParameters[5].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[5].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[5].Descriptor.ShaderRegister = 4;

	//texDescriptorRanged
	D3D12_DESCRIPTOR_RANGE descriptorRange[1] = {};
	descriptorRange[0].BaseShaderRegister = 1;
	descriptorRange[0].NumDescriptors = 1;
	descriptorRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	//tex
	rootParameters[6].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[6].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[6].DescriptorTable.pDescriptorRanges = descriptorRange;
	rootParameters[6].DescriptorTable.NumDescriptorRanges = _countof(descriptorRange);

	//Sampler
	D3D12_STATIC_SAMPLER_DESC staticSamplers[1] = {};
	staticSamplers[0].Filter = D3D12_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	staticSamplers[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;

	staticSamplers[0].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	staticSamplers[0].MaxLOD = D3D12_FLOAT32_MAX;
	staticSamplers[0].ShaderRegister = 0;
	staticSamplers[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	descriptionRootSignature.pStaticSamplers = staticSamplers;
	descriptionRootSignature.NumStaticSamplers = _countof(staticSamplers);

	descriptionRootSignature.pParameters = rootParameters;
	descriptionRootSignature.NumParameters = _countof(rootParameters);

	//RootSignature�쐬
	CreateGraphicsPiplineFanc::CreateRootSignature(
		device, descriptionRootSignature, SpritePSO);

	//InputLayout�̐ݒ�
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[2] = {};
	//Position
	CreateGraphicsPiplineFanc::SettingInputElementDesc(
		inputElementDescs[0],
		"POSITION",
		0,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		D3D12_APPEND_ALIGNED_ELEMENT
	);
	//Texcoord
	CreateGraphicsPiplineFanc::SettingInputElementDesc(
		inputElementDescs[1],
		"TEXCOORD",
		0,
		DXGI_FORMAT_R32G32_FLOAT,
		D3D12_APPEND_ALIGNED_ELEMENT
	);

	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	inputLayoutDesc.pInputElementDescs = inputElementDescs;
	inputLayoutDesc.NumElements = _countof(inputElementDescs);

	//BlendState
	D3D12_BLEND_DESC blendDesc{};
	D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = blendDesc.RenderTarget[0];
	CreateGraphicsPiplineFanc::SettingBlendState(blenddesc, BlendAdd);

	//RasterrizerState�ڐݒ�
	D3D12_RASTERIZER_DESC rasterizerDesc{};
	CreateGraphicsPiplineFanc::SettingRasterizer(
		rasterizerDesc,
		D3D12_CULL_MODE_BACK,
		D3D12_FILL_MODE_SOLID
	);


	D3D12_DEPTH_STENCIL_DESC despthStencilDesc{};
	CreateGraphicsPiplineFanc::SettingDepth(
		despthStencilDesc,
		true,
		D3D12_DEPTH_WRITE_MASK_ZERO,
		D3D12_COMPARISON_FUNC_LESS_EQUAL);


	//PSO作成
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};

	graphicsPipelineStateDesc.pRootSignature = SpritePSO.rootSignature.Get(); //RootSignature
	graphicsPipelineStateDesc.InputLayout = inputLayoutDesc; //InputLayout
	graphicsPipelineStateDesc.VS = { shader.vertexBlob->GetBufferPointer(),
	shader.vertexBlob->GetBufferSize() }; //VertexShader
	graphicsPipelineStateDesc.PS = { shader.pixelBlob->GetBufferPointer(),
	shader.pixelBlob->GetBufferSize() }; //PixeShader
	graphicsPipelineStateDesc.BlendState = blendDesc; //BlendState
	graphicsPipelineStateDesc.RasterizerState = rasterizerDesc; //RasterizerState
	graphicsPipelineStateDesc.DepthStencilState = despthStencilDesc;
	graphicsPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;


	graphicsPipelineStateDesc.NumRenderTargets = 1;
	graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;


	graphicsPipelineStateDesc.PrimitiveTopologyType =
		D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	graphicsPipelineStateDesc.SampleDesc.Count = 1;
	graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

	HRESULT hr = {};
	hr = device->CreateGraphicsPipelineState(&graphicsPipelineStateDesc,
		IID_PPV_ARGS(&SpritePSO.GraphicsPipelineState));
	assert(SUCCEEDED(hr));

	return SpritePSO;
}


//
//SPSOProperty GraphicsPipelineManager::CreatePBR(ComPtr<ID3D12Device> device, Commands commands, SShaderMode shader)
//{
//	SPSOProperty DirectionalLightPSO;
//
//
//	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
//
//	descriptionRootSignature.Flags =
//		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
//
//	D3D12_ROOT_PARAMETER rootParameters[8] = {};
//
//	//Material
//	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
//	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
//	rootParameters[0].Descriptor.ShaderRegister = 0;
//	//worldTransform
//	rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
//	rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
//	rootParameters[1].Descriptor.ShaderRegister = 0;
//	//view行列
//	rootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
//	rootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
//	rootParameters[2].Descriptor.ShaderRegister = 1;
//	//view行列
//	rootParameters[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
//	rootParameters[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
//	rootParameters[3].Descriptor.ShaderRegister = 2;
//	//LightData
//	D3D12_DESCRIPTOR_RANGE descriptorRangeForInstancing[1] = {};
//	descriptorRangeForInstancing[0].BaseShaderRegister = 0;
//	descriptorRangeForInstancing[0].NumDescriptors = 1;
//	descriptorRangeForInstancing[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
//	descriptorRangeForInstancing[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
//
//	rootParameters[4].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
//	rootParameters[4].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
//	rootParameters[4].DescriptorTable.pDescriptorRanges = descriptorRangeForInstancing;
//	rootParameters[4].DescriptorTable.NumDescriptorRanges = _countof(descriptorRangeForInstancing);
//
//	//今のLightの個数
//	rootParameters[5].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
//	rootParameters[5].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
//	rootParameters[5].Descriptor.ShaderRegister = 4;
//
//	//texDescriptorRanged
//	D3D12_DESCRIPTOR_RANGE descriptorRange[1] = {};
//	descriptorRange[0].BaseShaderRegister = 1;
//	descriptorRange[0].NumDescriptors = 1;
//	descriptorRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
//	descriptorRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
//
//	//tex
//	rootParameters[6].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
//	rootParameters[6].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
//	rootParameters[6].DescriptorTable.pDescriptorRanges = descriptorRange;
//	rootParameters[6].DescriptorTable.NumDescriptorRanges = _countof(descriptorRange);
//	//texDescriptorRanged
//	D3D12_DESCRIPTOR_RANGE NormalDescriptorRange[1] = {};
//	NormalDescriptorRange[0].BaseShaderRegister = 2;
//	NormalDescriptorRange[0].NumDescriptors = 1;
//	NormalDescriptorRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
//	NormalDescriptorRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
//
//	//tex
//	rootParameters[7].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
//	rootParameters[7].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
//	rootParameters[7].DescriptorTable.pDescriptorRanges = NormalDescriptorRange;
//	rootParameters[7].DescriptorTable.NumDescriptorRanges = _countof(NormalDescriptorRange);
//
//	//Sampler�̐ݒ�
//	D3D12_STATIC_SAMPLER_DESC staticSamplers[1] = {};
//	staticSamplers[0].Filter = D3D12_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
//	staticSamplers[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
//	staticSamplers[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
//	staticSamplers[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
//
//	staticSamplers[0].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
//	staticSamplers[0].MaxLOD = D3D12_FLOAT32_MAX;
//	staticSamplers[0].ShaderRegister = 0;
//	staticSamplers[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
//
//	descriptionRootSignature.pStaticSamplers = staticSamplers;
//	descriptionRootSignature.NumStaticSamplers = _countof(staticSamplers);
//
//
//	descriptionRootSignature.pParameters = rootParameters;
//	descriptionRootSignature.NumParameters = _countof(rootParameters);
//
//	ComPtr<ID3DBlob> signatureBlob = nullptr;
//	ComPtr<ID3DBlob> errorBlob = nullptr;
//	HRESULT hr = D3D12SerializeRootSignature(&descriptionRootSignature,
//		D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
//	if (FAILED(hr))
//	{
//		LogManager::Log(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
//		assert(false);
//	}
//
//	hr = device->CreateRootSignature(0, signatureBlob->GetBufferPointer(),
//		signatureBlob->GetBufferSize(), IID_PPV_ARGS(&DirectionalLightPSO.rootSignature));
//	assert(SUCCEEDED(hr));
//
//
//	//Output
//	D3D12_INPUT_ELEMENT_DESC inputElementDescs[6] = {};
//	inputElementDescs[0].SemanticName = "POSITION";
//	inputElementDescs[0].SemanticIndex = 0;
//	inputElementDescs[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
//	inputElementDescs[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
//
//	inputElementDescs[1].SemanticName = "TEXCOORD";
//	inputElementDescs[1].SemanticIndex = 0;
//	inputElementDescs[1].Format = DXGI_FORMAT_R32G32_FLOAT;
//	inputElementDescs[1].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
//
//	inputElementDescs[2].SemanticName = "NORMAL";
//	inputElementDescs[2].SemanticIndex = 0;
//	inputElementDescs[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
//	inputElementDescs[2].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
//
//	inputElementDescs[3].SemanticName = "WORLDPOSITION";
//	inputElementDescs[3].SemanticIndex = 0;
//	inputElementDescs[3].Format = DXGI_FORMAT_R32G32B32_FLOAT;
//	inputElementDescs[3].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
//
//	inputElementDescs[4].SemanticName = "WEIGHT";
//	inputElementDescs[4].SemanticIndex = 0;
//	inputElementDescs[4].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
//	inputElementDescs[4].InputSlot = 1;
//	inputElementDescs[4].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
//
//	inputElementDescs[5].SemanticName = "INDEX";
//	inputElementDescs[5].SemanticIndex = 0;
//	inputElementDescs[5].Format = DXGI_FORMAT_R32G32B32A32_SINT;
//	inputElementDescs[5].InputSlot = 1;
//	inputElementDescs[5].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
//
//	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
//	inputLayoutDesc.pInputElementDescs = inputElementDescs;
//	inputLayoutDesc.NumElements = _countof(inputElementDescs);
//
//
//	D3D12_BLEND_DESC blendDesc{};
//	//���ׂĂ̐F�v�f���������
//	blendDesc.RenderTarget[0].RenderTargetWriteMask =
//		D3D12_COLOR_WRITE_ENABLE_ALL;
//
//
//	//RasterrizerState�ڐݒ�
//	D3D12_RASTERIZER_DESC rasterizerDesc{};
//
//	//���ʁi���v���j��\�����Ȃ�
//	rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
//	//�O�p�`�̒���h��Ԃ�
//	rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
//
//	D3D12_DEPTH_STENCIL_DESC despthStencilDesc{};
//	despthStencilDesc.DepthEnable = true;
//	despthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
//	despthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
//
//	//PSO�̐���
//	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};
//
//	graphicsPipelineStateDesc.pRootSignature = DirectionalLightPSO.rootSignature.Get(); //RootSignature
//	graphicsPipelineStateDesc.InputLayout = inputLayoutDesc; //InputLayout
//	graphicsPipelineStateDesc.VS = { shader.vertexBlob->GetBufferPointer(),
//	shader.vertexBlob->GetBufferSize() }; //VertexShader
//	graphicsPipelineStateDesc.PS = { shader.pixelBlob->GetBufferPointer(),
//	shader.pixelBlob->GetBufferSize() }; //PixeShader
//	graphicsPipelineStateDesc.BlendState = blendDesc; //BlendState
//	graphicsPipelineStateDesc.RasterizerState = rasterizerDesc; //RasterizerState
//	graphicsPipelineStateDesc.DepthStencilState = despthStencilDesc;
//	graphicsPipelineStateDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
//
//	//��������RTV�̏��
//	graphicsPipelineStateDesc.NumRenderTargets = 1;
//	graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
//
//	//���p����g�|���W(�`��)�̃^�C�v�B�O�p�`
//	graphicsPipelineStateDesc.PrimitiveTopologyType =
//		D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
//
//	//�ǂ̂悤�ɉ�ʂɐF��ł����ނ��̐ݒ�(�C�ɂ��Ȃ��ėǂ�)
//	graphicsPipelineStateDesc.SampleDesc.Count = 1;
//	graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
//
//	hr = device->CreateGraphicsPipelineState(&graphicsPipelineStateDesc,
//		IID_PPV_ARGS(&DirectionalLightPSO.GraphicsPipelineState));
//	assert(SUCCEEDED(hr));
//
//	return DirectionalLightPSO;
//}


SPSOProperty GraphicsPipelineManager::CreateParticle3dNone(ComPtr<ID3D12Device> device, Commands commands, SShaderMode shader)
{
	SPSOProperty ParticlePSO;

	//RootSignature�쐬
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};

	//descriptionRootSignature = CreateDescriptRootSignature();
	descriptionRootSignature.Flags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	//Material�ݒ�
	D3D12_ROOT_PARAMETER rootParameters[3] = {};
	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[0].Descriptor.ShaderRegister = 0;

	//Instansing
	D3D12_DESCRIPTOR_RANGE descriptorRangeForInstancing[1] = {};
	descriptorRangeForInstancing[0].BaseShaderRegister = 0;
	descriptorRangeForInstancing[0].NumDescriptors = 1;
	descriptorRangeForInstancing[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRangeForInstancing[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	//Vertex��Transform
	rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rootParameters[1].DescriptorTable.pDescriptorRanges = descriptorRangeForInstancing;
	rootParameters[1].DescriptorTable.NumDescriptorRanges = _countof(descriptorRangeForInstancing);

	//PixcelDescriptorRanged
	D3D12_DESCRIPTOR_RANGE descriptorRange[1] = {};
	descriptorRange[0].BaseShaderRegister = 0;
	descriptorRange[0].NumDescriptors = 1;
	descriptorRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	//rootPrameter�ɓ����
	rootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[2].DescriptorTable.pDescriptorRanges = descriptorRange;
	rootParameters[2].DescriptorTable.NumDescriptorRanges = _countof(descriptorRange);

	//Sampler�̐ݒ�

	D3D12_STATIC_SAMPLER_DESC staticSamplers[1] = {};
	staticSamplers[0].Filter = D3D12_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	staticSamplers[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;

	staticSamplers[0].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	staticSamplers[0].MaxLOD = D3D12_FLOAT32_MAX;
	staticSamplers[0].ShaderRegister = 0;
	staticSamplers[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	descriptionRootSignature.pStaticSamplers = staticSamplers;
	descriptionRootSignature.NumStaticSamplers = _countof(staticSamplers);

	descriptionRootSignature.pParameters = rootParameters;
	descriptionRootSignature.NumParameters = _countof(rootParameters);

	//RootSignature�쐬
	CreateGraphicsPiplineFanc::CreateRootSignature(device, descriptionRootSignature, ParticlePSO);

	//InputLayout�̐ݒ�
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[3] = {};
	//Position
	CreateGraphicsPiplineFanc::SettingInputElementDesc(
		inputElementDescs[0],
		"POSITION",
		0,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		D3D12_APPEND_ALIGNED_ELEMENT
	);
	//Texcoord
	CreateGraphicsPiplineFanc::SettingInputElementDesc(
		inputElementDescs[1],
		"TEXCOORD",
		0,
		DXGI_FORMAT_R32G32_FLOAT,
		D3D12_APPEND_ALIGNED_ELEMENT
	);
	CreateGraphicsPiplineFanc::SettingInputElementDesc(
		inputElementDescs[2],
		"COLOR",
		0,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		D3D12_APPEND_ALIGNED_ELEMENT
	);
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	inputLayoutDesc.pInputElementDescs = inputElementDescs;
	inputLayoutDesc.NumElements = _countof(inputElementDescs);

	//BlendState�̐ݒ�
	D3D12_BLEND_DESC blendDesc{};
	D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = blendDesc.RenderTarget[0];
	CreateGraphicsPiplineFanc::SettingBlendState(blenddesc, BlendNone);

	//RasterrizerState�ڐݒ�
	D3D12_RASTERIZER_DESC rasterizerDesc{};
	CreateGraphicsPiplineFanc::SettingRasterizer(
		rasterizerDesc,
		D3D12_CULL_MODE_BACK,
		D3D12_FILL_MODE_SOLID
	);

	//�[�x�ݒ�
	D3D12_DEPTH_STENCIL_DESC despthStencilDesc{};
	CreateGraphicsPiplineFanc::SettingDepth(
		despthStencilDesc,
		true,
		D3D12_DEPTH_WRITE_MASK_ZERO,
		D3D12_COMPARISON_FUNC_LESS_EQUAL
	);

	//PSO�̐���
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};

	graphicsPipelineStateDesc.pRootSignature = ParticlePSO.rootSignature.Get(); //RootSignature
	graphicsPipelineStateDesc.InputLayout = inputLayoutDesc; //InputLayout
	graphicsPipelineStateDesc.VS = { shader.vertexBlob->GetBufferPointer(),
	shader.vertexBlob->GetBufferSize() }; //VertexShader
	graphicsPipelineStateDesc.PS = { shader.pixelBlob->GetBufferPointer(),
	shader.pixelBlob->GetBufferSize() }; //PixeShader
	graphicsPipelineStateDesc.BlendState = blendDesc; //BlendState
	graphicsPipelineStateDesc.RasterizerState = rasterizerDesc; //RasterizerState
	graphicsPipelineStateDesc.DepthStencilState = despthStencilDesc;
	graphicsPipelineStateDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;


	//��������RTV�̏��
	graphicsPipelineStateDesc.NumRenderTargets = 1;
	graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;

	//���p����g�|���W(�`��)�̃^�C�v�B�O�p�`
	graphicsPipelineStateDesc.PrimitiveTopologyType =
		D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	//�ǂ̂悤�ɉ�ʂɐF��ł����ނ��̐ݒ�(�C�ɂ��Ȃ��ėǂ�)
	graphicsPipelineStateDesc.SampleDesc.Count = 1;
	graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

	HRESULT hr = {};
	hr = device->CreateGraphicsPipelineState(&graphicsPipelineStateDesc,
		IID_PPV_ARGS(&ParticlePSO.GraphicsPipelineState));
	assert(SUCCEEDED(hr));

	return ParticlePSO;
}

SPSOProperty GraphicsPipelineManager::CreateParticle3dAdd(ComPtr<ID3D12Device> device, Commands commands, SShaderMode shader)
{
	SPSOProperty ParticlePSO;

	//RootSignature�쐬
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};

	descriptionRootSignature.Flags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	//Material�ݒ�
	D3D12_ROOT_PARAMETER rootParameters[3] = {};
	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[0].Descriptor.ShaderRegister = 0;

	//Vertex
	D3D12_DESCRIPTOR_RANGE descriptorRangeForInstancing[1] = {};
	descriptorRangeForInstancing[0].BaseShaderRegister = 0;
	descriptorRangeForInstancing[0].NumDescriptors = 1;
	descriptorRangeForInstancing[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRangeForInstancing[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	//Vertex��Transform
	rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rootParameters[1].DescriptorTable.pDescriptorRanges = descriptorRangeForInstancing;
	rootParameters[1].DescriptorTable.NumDescriptorRanges = _countof(descriptorRangeForInstancing);
	//


	//PixcelDescriptorRanged
	D3D12_DESCRIPTOR_RANGE descriptorRange[1] = {};
	descriptorRange[0].BaseShaderRegister = 0;
	descriptorRange[0].NumDescriptors = 1;
	descriptorRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	//rootPrameter�ɓ����
	rootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[2].DescriptorTable.pDescriptorRanges = descriptorRange;
	rootParameters[2].DescriptorTable.NumDescriptorRanges = _countof(descriptorRange);


	//Sampler�̐ݒ�

	D3D12_STATIC_SAMPLER_DESC staticSamplers[1] = {};
	staticSamplers[0].Filter = D3D12_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	staticSamplers[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;

	staticSamplers[0].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	staticSamplers[0].MaxLOD = D3D12_FLOAT32_MAX;
	staticSamplers[0].ShaderRegister = 0;
	staticSamplers[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	descriptionRootSignature.pStaticSamplers = staticSamplers;
	descriptionRootSignature.NumStaticSamplers = _countof(staticSamplers);

	descriptionRootSignature.pParameters = rootParameters;
	descriptionRootSignature.NumParameters = _countof(rootParameters);

	//RootSignature�쐬
	CreateGraphicsPiplineFanc::CreateRootSignature(device, descriptionRootSignature, ParticlePSO);

	//InputLayout�̐ݒ�
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[3] = {};
	//Position
	CreateGraphicsPiplineFanc::SettingInputElementDesc(
		inputElementDescs[0],
		"POSITION",
		0,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		D3D12_APPEND_ALIGNED_ELEMENT
	);
	//Texcoord
	CreateGraphicsPiplineFanc::SettingInputElementDesc(
		inputElementDescs[1],
		"TEXCOORD",
		0,
		DXGI_FORMAT_R32G32_FLOAT,
		D3D12_APPEND_ALIGNED_ELEMENT
	);
	CreateGraphicsPiplineFanc::SettingInputElementDesc(
		inputElementDescs[2],
		"COLOR",
		0,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		D3D12_APPEND_ALIGNED_ELEMENT
	);
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	inputLayoutDesc.pInputElementDescs = inputElementDescs;
	inputLayoutDesc.NumElements = _countof(inputElementDescs);

	//BlendState�̐ݒ�
	D3D12_BLEND_DESC blendDesc{};
	D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = blendDesc.RenderTarget[0];
	CreateGraphicsPiplineFanc::SettingBlendState(blenddesc, BlendAdd);

	//RasterrizerState�ڐݒ�
	D3D12_RASTERIZER_DESC rasterizerDesc{};
	CreateGraphicsPiplineFanc::SettingRasterizer(
		rasterizerDesc,
		D3D12_CULL_MODE_BACK,
		D3D12_FILL_MODE_SOLID
	);

	//�[�x�ݒ�
	D3D12_DEPTH_STENCIL_DESC despthStencilDesc{};
	CreateGraphicsPiplineFanc::SettingDepth(
		despthStencilDesc,
		true,
		D3D12_DEPTH_WRITE_MASK_ZERO,
		D3D12_COMPARISON_FUNC_LESS_EQUAL
	);

	//PSO�̐���
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};

	graphicsPipelineStateDesc.pRootSignature = ParticlePSO.rootSignature.Get(); //RootSignature
	graphicsPipelineStateDesc.InputLayout = inputLayoutDesc; //InputLayout
	graphicsPipelineStateDesc.VS = { shader.vertexBlob->GetBufferPointer(),
	shader.vertexBlob->GetBufferSize() }; //VertexShader
	graphicsPipelineStateDesc.PS = { shader.pixelBlob->GetBufferPointer(),
	shader.pixelBlob->GetBufferSize() }; //PixeShader
	graphicsPipelineStateDesc.BlendState = blendDesc; //BlendState
	graphicsPipelineStateDesc.RasterizerState = rasterizerDesc; //RasterizerState
	graphicsPipelineStateDesc.DepthStencilState = despthStencilDesc;
	graphicsPipelineStateDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;

	//��������RTV�̏��
	graphicsPipelineStateDesc.NumRenderTargets = 1;
	graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;

	//���p����g�|���W(�`��)�̃^�C�v�B�O�p�`
	graphicsPipelineStateDesc.PrimitiveTopologyType =
		D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	//�ǂ̂悤�ɉ�ʂɐF��ł����ނ��̐ݒ�(�C�ɂ��Ȃ��ėǂ�)
	graphicsPipelineStateDesc.SampleDesc.Count = 1;
	graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

	HRESULT hr = {};
	hr = device->CreateGraphicsPipelineState(&graphicsPipelineStateDesc,
		IID_PPV_ARGS(&ParticlePSO.GraphicsPipelineState));
	assert(SUCCEEDED(hr));

	return ParticlePSO;
}

SPSOProperty GraphicsPipelineManager::CreatePostEffectTest(ComPtr<ID3D12Device> device, Commands commands, SShaderMode shader)
{

	SPSOProperty SpritePSO;

	//RootSignature
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	descriptionRootSignature.Flags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;


	D3D12_ROOT_PARAMETER rootParameters[11] = {};

	//matrix
	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rootParameters[0].Descriptor.ShaderRegister = 0;

	//param
	rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[1].Descriptor.ShaderRegister = 1;

	//tex
	D3D12_DESCRIPTOR_RANGE descriptorRange[1] = {};
	descriptorRange[0].BaseShaderRegister = 0;
	descriptorRange[0].NumDescriptors = 1;
	descriptorRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[2].DescriptorTable.pDescriptorRanges = descriptorRange;
	rootParameters[2].DescriptorTable.NumDescriptorRanges = _countof(descriptorRange);
	//shadow
	D3D12_DESCRIPTOR_RANGE shadowDescriptorRange[1] = {};
	shadowDescriptorRange[0].BaseShaderRegister = 1;
	shadowDescriptorRange[0].NumDescriptors = 1;
	shadowDescriptorRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	shadowDescriptorRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[3].DescriptorTable.pDescriptorRanges = shadowDescriptorRange;
	rootParameters[3].DescriptorTable.NumDescriptorRanges = _countof(shadowDescriptorRange);
	//Blurparam
	rootParameters[4].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[4].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[4].Descriptor.ShaderRegister = 2;
	//Colorparam
	rootParameters[5].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[5].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[5].Descriptor.ShaderRegister = 3;
	//DirectionLight
	rootParameters[6].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[6].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[6].Descriptor.ShaderRegister = 4;

	rootParameters[7].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[7].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rootParameters[7].Descriptor.ShaderRegister = 5;
	//view
	rootParameters[8].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[8].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rootParameters[8].Descriptor.ShaderRegister = 6;
	//view
	rootParameters[9].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[9].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[9].Descriptor.ShaderRegister = 7;

	//shadow
	D3D12_DESCRIPTOR_RANGE colorDescriptorRange[1] = {};
	colorDescriptorRange[0].BaseShaderRegister = 3;
	colorDescriptorRange[0].NumDescriptors = 1;
	colorDescriptorRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	colorDescriptorRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[10].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[10].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameters[10].DescriptorTable.pDescriptorRanges = colorDescriptorRange;
	rootParameters[10].DescriptorTable.NumDescriptorRanges = _countof(colorDescriptorRange);
	
	//Sampler�̐ݒ�
	D3D12_STATIC_SAMPLER_DESC staticSamplers[2] = {};
	staticSamplers[0].Filter = D3D12_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	staticSamplers[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;

	staticSamplers[0].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	staticSamplers[0].MaxLOD = D3D12_FLOAT32_MAX;
	staticSamplers[0].ShaderRegister = 0;
	staticSamplers[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	//Point
	staticSamplers[1].Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
	staticSamplers[1].AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	staticSamplers[1].AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	staticSamplers[1].AddressW = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	staticSamplers[1].ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
	staticSamplers[1].MaxLOD = D3D12_FLOAT32_MAX;
	staticSamplers[1].ShaderRegister = 1;  // Register slot 1
	staticSamplers[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	descriptionRootSignature.pStaticSamplers = staticSamplers;
	descriptionRootSignature.NumStaticSamplers = _countof(staticSamplers);
	descriptionRootSignature.pParameters = rootParameters;
	descriptionRootSignature.NumParameters = _countof(rootParameters);

	//rootSignature�̍쐬
	CreateGraphicsPiplineFanc::CreateRootSignature(device, descriptionRootSignature, SpritePSO);


	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	inputLayoutDesc.pInputElementDescs = nullptr;
	inputLayoutDesc.NumElements = 0;

	const int numRenderTargets = 2;
	D3D12_RT_FORMAT_ARRAY rtvFormats = {};
	rtvFormats.NumRenderTargets = numRenderTargets;
	rtvFormats.RTFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM; // AOutputのフォーマット
	rtvFormats.RTFormats[1] = DXGI_FORMAT_R8G8B8A8_UNORM; // BOutputのフォーマット

	//BlendState�̐ݒ��s��
	D3D12_BLEND_DESC blendDesc{};
	D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = blendDesc.RenderTarget[0];
	CreateGraphicsPiplineFanc::SettingBlendState(blenddesc, BlendNone);


	//RasterrizerStat
	D3D12_RASTERIZER_DESC rasterizerDesc{};
	CreateGraphicsPiplineFanc::SettingRasterizer(
		rasterizerDesc,
		D3D12_CULL_MODE_BACK,
		D3D12_FILL_MODE_SOLID);

	//depth
	D3D12_DEPTH_STENCIL_DESC despthStencilDesc{};
	CreateGraphicsPiplineFanc::SettingDepth(despthStencilDesc,
		false,
		D3D12_DEPTH_WRITE_MASK_ALL,
		D3D12_COMPARISON_FUNC_LESS_EQUAL
	);

	//PSO�̐���
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};
	graphicsPipelineStateDesc.pRootSignature = SpritePSO.rootSignature.Get(); //RootSignature
	graphicsPipelineStateDesc.InputLayout = inputLayoutDesc; //InputLayout
	graphicsPipelineStateDesc.VS = { shader.vertexBlob->GetBufferPointer(),
	shader.vertexBlob->GetBufferSize() }; //VertexShader
	graphicsPipelineStateDesc.PS = { shader.pixelBlob->GetBufferPointer(),
	shader.pixelBlob->GetBufferSize() }; //PixeShader
	graphicsPipelineStateDesc.BlendState = blendDesc; //BlendState
	graphicsPipelineStateDesc.RasterizerState = rasterizerDesc; //RasterizerState
	graphicsPipelineStateDesc.DepthStencilState = despthStencilDesc;
	graphicsPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;


	//RTVの設定
	graphicsPipelineStateDesc.NumRenderTargets = 2;
	graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	graphicsPipelineStateDesc.RTVFormats[1] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;

	//���p����g�|���W(�`��)�̃^�C�v�B�O�p�`
	graphicsPipelineStateDesc.PrimitiveTopologyType =
		D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	//�ǂ̂悤�ɉ�ʂɐF��ł����ނ��̐ݒ�(�C�ɂ��Ȃ��ėǂ�)
	graphicsPipelineStateDesc.SampleDesc.Count = 1;
	graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

	HRESULT hr = {};
	hr = device->CreateGraphicsPipelineState(&graphicsPipelineStateDesc,
		IID_PPV_ARGS(&SpritePSO.GraphicsPipelineState));
	assert(SUCCEEDED(hr));

	return SpritePSO;
}
