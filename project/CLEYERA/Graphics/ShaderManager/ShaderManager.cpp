#include "ShaderManager.h"


ShaderManager* ShaderManager::Getinstance()
{
	static ShaderManager instance;
	return &instance;
}

void ShaderManager::Initialize()
{
	DxcCreate();
	includeHandlerSetting();
	ShaderComples();
	Particles();
}

IDxcBlob* ShaderManager::CompilerShaderFanc(const std::wstring& filePath, const wchar_t* profile)
{
	ComPtr<IDxcUtils> dxcUtils = ShaderManager::Getinstance()->dxc.m_pUtils.Get();
	ComPtr<IDxcCompiler3> dxcCompiler = ShaderManager::Getinstance()->dxc.m_pCompiler.Get();
	ComPtr<IDxcIncludeHandler> includeHandler = ShaderManager::Getinstance()->dxc.m_pIncludeHandler.Get();

	//1.hlsl�t�@�C����ǂ�
	LogManager::Log(LogManager::ConvertString(std::format(L"Begin CompileShader,path:{},profile:{}\n", filePath, profile)));
	//hlsl�t�@�C����ǂ�
	IDxcBlobEncoding* shaderSource = nullptr;
	HRESULT hr =
		dxcUtils->LoadFile(filePath.c_str(), nullptr, &shaderSource);
	//�ǂ߂Ȃ�������~�߂�
	assert(SUCCEEDED(hr));
	//�ǂݍ��񂾃t�@�C���̓�e��ݒ肷��
	DxcBuffer shaderSourceBuffer;
	shaderSourceBuffer.Ptr = shaderSource->GetBufferPointer();
	shaderSourceBuffer.Size = shaderSource->GetBufferSize();
	shaderSourceBuffer.Encoding = DXC_CP_UTF8;

	//2.Compile����
	LPCWSTR arguments[] = {
		filePath.c_str(),
		L"-E",L"main",
		L"-T",profile,
		L"-Zi",L"-Qembed_debug",
		L"-Od",
		L"-Zpr",
	};

	//���ۂ�Shader��R���p�C������
	IDxcResult* shaderResult = nullptr;
	hr = dxcCompiler->Compile(&shaderSourceBuffer, arguments, _countof(arguments), includeHandler.Get(), IID_PPV_ARGS(&shaderResult));
	//�R���p�C���G���[�ł͂Ȃ�dxc���N���o���Ȃ��Ȃǒv���I�ȏ�
	assert(SUCCEEDED(hr));

	//3.�x���E�G���[���o�Ă��Ȃ�����m�F����
	//�x���E�G���[���o�Ă��烍�O�ɏo���Ď~�߂�
	IDxcBlobUtf8* shaderError = nullptr;
	shaderResult->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&shaderError), nullptr);
	if (shaderError != nullptr && shaderError->GetStringLength() != 0) {
		LogManager::Log(shaderError->GetStringPointer());
		assert(false);
	}
	//4.Compile���ʂ�󂯎���ĕԂ�
	//BLOB�E�E�EBinaryLargeOBject
	IDxcBlob* shaderBlob = nullptr;
	hr = shaderResult->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&shaderBlob), nullptr);
	assert(SUCCEEDED(hr));
	//�����������O��o��
	LogManager::Log(LogManager::ConvertString(std::format(L"Compile Succeeded,path:{},profile:{}\n", filePath, profile)));
	//����g��Ȃ����\�[�X����
	shaderSource->Release();
	shaderResult->Release();
	//���s�p�̃o�C�i����ԋp
	return shaderBlob;

}


void ShaderManager::DxcCreate()
{
	HRESULT hr = {};

	hr = DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&ShaderManager::Getinstance()->dxc.m_pUtils));
	assert(SUCCEEDED(hr));

	hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&ShaderManager::Getinstance()->dxc.m_pCompiler));
	assert(SUCCEEDED(hr));
}

void ShaderManager::includeHandlerSetting()
{
	ShaderManager::Getinstance()->dxc.m_pUtils->CreateDefaultIncludeHandler(&ShaderManager::Getinstance()->dxc.m_pIncludeHandler);
}

void ShaderManager::ShaderComples()
{
	auto instance = ShaderManager::Getinstance();
	instance->shaders[Shader::SPRITE_2d]["None"].vertexBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Sprite2d/SpriteObject2d.VS.hlsl",
			L"vs_6_0");
	instance->shaders[Shader::SPRITE_2d]["None"].pixelBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Sprite2d/SpriteObject2d.PS.hlsl",
			L"ps_6_0");

	//Dissolve
	instance->shaders[Shader::SPRITE_2d]["Dissolve"].vertexBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Sprite2d/SpriteObject2d.VS.hlsl",
			L"vs_6_0");
	instance->shaders[Shader::SPRITE_2d]["Dissolve"].pixelBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Sprite2d/SpriteObject2d_Dissolve.PS.hlsl",
			L"ps_6_0");


	ShapeShader();
	Sprite3dShader();
	Sprite2dShader();
	CreateLineShader();
	//PBR_ModelShader();
	//PhongModelShader();
	ParticleShader();
	PhongNormalModel();
	PhongSubsurfaceModel();
	PhongNormalInstancingModel();
	Phong_DissolveShader();

	ColorPostProcess();

	PostEffectTest();
	ShadowMap();
	SkyBoxModel();

	SkinningPhongModelShader();
	CompileSkinningCs();
}

void ShaderManager::ShapeShader()
{
	SShaderMode shaders; shaders;
	shaders.vertexBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/ShapeObject3d.VS.hlsl",
			L"vs_6_0");
	shaders.pixelBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/ShapeObject3d.PS.hlsl",
			L"ps_6_0");
	ShaderManager::Getinstance()->shaders_.shape = shaders;
}

void ShaderManager::Sprite3dShader()
{
	SShaderMode shaders;
	shaders.vertexBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/SpriteObject3d.VS.hlsl",
			L"vs_6_0");

	shaders.pixelBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/SpriteObject3d.PS.hlsl",
			L"ps_6_0");

	ShaderManager::Getinstance()->shaders_.sprite3d = shaders;
}

void ShaderManager::Sprite2dShader()
{
	SShaderMode shaders;
	shaders.vertexBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Sprite2d/SpriteObject2d.VS.hlsl",
			L"vs_6_0");

	shaders.pixelBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Sprite2d/SpriteObject2d.PS.hlsl",
			L"ps_6_0");

	ShaderManager::Getinstance()->shaders_.sprite2d = shaders;
}

void ShaderManager::PBR_ModelShader()
{
	SShaderMode shaders;
	shaders.vertexBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/PBR_ModelObject3d.VS.hlsl",
			L"vs_6_0");

	shaders.pixelBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/PBR_ModelObject3d.PS.hlsl",
			L"ps_6_0");
	ShaderManager::Getinstance()->shaders_.PBR_Model = shaders;
}

void ShaderManager::PhongModelShader()
{
}

void ShaderManager::Phong_DissolveShader()
{
	SShaderMode shaders;
	shaders.vertexBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Phong/Phong_NormalMap_Model3dObject.VS.hlsl",
			L"vs_6_0");

	shaders.pixelBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Phong/Phong_Dissolve_Model3dObject.PS.hlsl",
			L"ps_6_0");

	ShaderManager::Getinstance()->shaders_.Phong_Dissolve_Model = shaders;
}

void ShaderManager::ParticleShader()
{

}
void ShaderManager::PhongNormalModel()
{
	SShaderMode shaders;
	shaders.vertexBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Phong/Phong_NormalMap_Model3dObject.VS.hlsl",
			L"vs_6_0");

	shaders.pixelBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Phong/Phong_NormalMap_Model3dObject.PS.hlsl",
			L"ps_6_0");

	ShaderManager::Getinstance()->shaders_.Phong_Normal_Model = shaders;
}

void ShaderManager::PhongSubsurfaceModel()
{
	SShaderMode shaders;
	shaders.vertexBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Phong/Phong_Subsurface_Model3dObject.VS.hlsl",
			L"vs_6_0");

	shaders.pixelBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Phong/Phong_Subsurface_Model3dObject.PS.hlsl",
			L"ps_6_0");

	ShaderManager::Getinstance()->shaders_.Phong_subsurface_Model = shaders;
}

void ShaderManager::PhongNormalInstancingModel()
{
	SShaderMode shaders;
	shaders.vertexBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Phong/Phong_NormalMap_ModelInstancing3dObject.VS.hlsl",
			L"vs_6_0");

	shaders.pixelBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Phong/Phong_NormalMap_ModelINstancing3dObject.PS.hlsl",
			L"ps_6_0");

	ShaderManager::Getinstance()->shaders_.Phong_Normal_InstancingModel = shaders;
}

void ShaderManager::CreateLineShader()
{
	SShaderMode shaders;
	shaders.vertexBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Line.VS.hlsl",
			L"vs_6_0");

	shaders.pixelBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Primitives.PS.hlsl",
			L"ps_6_0");

	ShaderManager::Getinstance()->shaders_.Line = shaders;
}

void ShaderManager::ColorPostProcess()
{
}


void ShaderManager::PostEffectTest()
{
	SShaderMode shaders;
	shaders.vertexBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/PostEffect/PostEffect.VS.hlsl",
			L"vs_6_0");

	shaders.pixelBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/PostEffect/PostEffect.PS.hlsl",
			L"ps_6_0");

	ShaderManager::Getinstance()->shaders_.PostEffect = shaders;
}

void ShaderManager::ShadowMap()
{
}

void ShaderManager::SkinningPhongModelShader()
{
	SShaderMode shaders{};
	shaders.vertexBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Phong/SkinningObject3d.VS.hlsl",
			L"vs_6_0");

	shaders.pixelBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Phong/Phong_NormalMap_Model3dObject.PS.hlsl",
			L"ps_6_0");
	ShaderManager::Getinstance()->shaders_.skinningPhongModel = shaders;
}

void ShaderManager::SkyBoxModel()
{
	SShaderMode shaders{};
	shaders.vertexBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/SkyBox.VS.hlsl",
			L"vs_6_0");

	shaders.pixelBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/SkyBox.PS.hlsl",
			L"ps_6_0");

	ShaderManager::Getinstance()->shaders_.SkyBoxModel = shaders;
}

void ShaderManager::CompileSkinningCs()
{

}

void ShaderManager::Particles()
{
	Particle_Init();
	Particle_Update();
	ParticleDebugDraw();
	Particle_EmitterSphere();
	Particle_EmitterBox();
	ShaderManager* instance = ShaderManager::Getinstance();
	
	instance->shaders[Shader::PARTICLE_EMITTER]["Box"].csBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Particle/Emitter/Particle_TypeBox.CS.hlsl",
			L"cs_6_0");
	instance->shaders[Shader::PARTICLE_EMITTER]["Sphere"].csBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Particle/Emitter/Particle_TypeShpere.CS.hlsl",
			L"cs_6_0");
	instance->shaders[Shader::PARTICLE_EMITTER]["Goal"].csBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Particle/Emitter/Particle_TypeCircleGoal.CS.hlsl",
			L"cs_6_0");
	instance->shaders[Shader::PARTICLE_FIELD]["Suction"].csBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Particle/Field/Particle_Field_TypeBox_Suction.CS.hlsl",
			L"cs_6_0");
}

void ShaderManager::Particle_Init()
{
	SShaderMode shaders{};
	shaders.csBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Particle/Particle_Init.CS.hlsl",
			L"cs_6_0");

	ShaderManager::Getinstance()->particleShader_.particleInit = shaders;
}

void ShaderManager::ParticleDebugDraw()
{

	SShaderMode shaders{};
	shaders.vertexBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Particle/Draw/Particle_DebugDraw.VS.hlsl",
			L"vs_6_0");
	shaders.pixelBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Particle/Draw/Particle_DebugDraw.PS.hlsl",
			L"ps_6_0");

	ShaderManager::Getinstance()->particleShader_.DebugDraw = shaders;
}

void ShaderManager::Particle_Update()
{

	SShaderMode shaders{};
	shaders.csBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Particle/Update/Particle_Update.CS.hlsl",
			L"cs_6_0");

	ShaderManager::Getinstance()->particleShader_.particleUpdate = shaders;
}

void ShaderManager::Particle_EmitterSphere()
{

	SShaderMode shaders{};
	shaders.csBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Particle/Emitter/Particle_TypeShpere.CS.hlsl",
			L"cs_6_0");

	ShaderManager::Getinstance()->particleShader_.particleSphereEmitter = shaders;
}

void ShaderManager::Particle_EmitterBox()
{

	SShaderMode shaders{};
	shaders.csBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Particle/Emitter/Particle_TypeBox.CS.hlsl",
			L"cs_6_0");

	ShaderManager::Getinstance()->particleShader_.particleBoxEmitter = shaders;
}
