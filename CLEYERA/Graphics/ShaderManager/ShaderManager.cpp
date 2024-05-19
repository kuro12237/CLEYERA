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
	LogManager::Log(LogManager:: ConvertString(std::format(L"Compile Succeeded,path:{},profile:{}\n", filePath, profile)));
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

	ColorModel();
	NormalModel();
	PosModel();
	ColorPostProcess();

	PostEffectTest();
	ShadowMap();

	SkinningPhongModelShader();
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
			L"Resources/Shader/SpriteObject2d.VS.hlsl",
			L"vs_6_0");

	shaders.pixelBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/SpriteObject2d.PS.hlsl",
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
	SShaderMode shaders;
	shaders.vertexBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Phong_ModelObject3d.VS.hlsl",
			L"vs_6_0");

	shaders.pixelBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Phong_ModelObject3d.PS.hlsl",
			L"ps_6_0");
	ShaderManager::Getinstance()->shaders_.Phong_Model = shaders;
}

void ShaderManager::ParticleShader()
{

	SShaderMode shaders;
	shaders.vertexBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/ParticleObject3d.VS.hlsl",
			L"vs_6_0");

	shaders.pixelBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/ParticleObject3d.PS.hlsl",
			L"ps_6_0");
	ShaderManager::Getinstance()->shaders_.Particle = shaders;

}
void ShaderManager::PhongNormalModel()
{
	SShaderMode shaders;
	shaders.vertexBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Phong_NormalMap_Model3dObject.VS.hlsl",
			L"vs_6_0");

	shaders.pixelBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Phong_NormalMap_Model3dObject.PS.hlsl",
			L"ps_6_0");

	ShaderManager::Getinstance()->shaders_.Phong_Normal_Model = shaders;
}

void ShaderManager::PhongSubsurfaceModel()
{
	SShaderMode shaders;
	shaders.vertexBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Phong_Subsurface_Model3dObject.VS.hlsl",
			L"vs_6_0");

	shaders.pixelBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Phong_Subsurface_Model3dObject.PS.hlsl",
			L"ps_6_0");

	ShaderManager::Getinstance()->shaders_.Phong_subsurface_Model = shaders;
}

void ShaderManager::PhongNormalInstancingModel()
{
	SShaderMode shaders;
	shaders.vertexBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Phong_NormalMap_ModelInstancing3dObject.VS.hlsl",
			L"vs_6_0");

	shaders.pixelBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Phong_NormalMap_ModelINstancing3dObject.PS.hlsl",
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

void ShaderManager::ColorModel()
{
	SShaderMode shaders;
	shaders.vertexBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Model/ColorObject3d.VS.hlsl",
			L"vs_6_0");

	shaders.pixelBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Model/ColorObject3d.PS.hlsl",
			L"ps_6_0");

	ShaderManager::Getinstance()->shaders_.ColorModel = shaders;
}

void ShaderManager::NormalModel()
{
	SShaderMode shaders;
	shaders.vertexBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Model/NormalObject3d.VS.hlsl",
			L"vs_6_0");

	shaders.pixelBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Model/NormalObject3d.PS.hlsl",
			L"ps_6_0");

	ShaderManager::Getinstance()->shaders_.NormalModel = shaders;
}

void ShaderManager::PosModel()
{
	SShaderMode shaders;
	shaders.vertexBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Model/WorldPositionObject3d.VS.hlsl",
			L"vs_6_0");

	shaders.pixelBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Model/WorldPositionObject3d.PS.hlsl",
			L"ps_6_0");

	ShaderManager::Getinstance()->shaders_.PosModel = shaders;
}

void ShaderManager::ColorPostProcess()
{
	SShaderMode shaders;
	shaders.vertexBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/PostEffect/DeferredShading.VS.hlsl",
			L"vs_6_0");

	shaders.pixelBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/PostEffect/DeferredShading.PS.hlsl",
			L"ps_6_0");

	ShaderManager::Getinstance()->shaders_.ColorPostProcess = shaders;
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

	ShaderManager::Getinstance()->shaders_.PostEffectTest = shaders;
}

void ShaderManager::ShadowMap()
{
	SShaderMode shaders;
	shaders.vertexBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/PostEffect/shadow.VS.hlsl",
			L"vs_6_0");
	shaders.pixelBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/PostEffect/shadow.PS.hlsl",
			L"ps_6_0");


	ShaderManager::Getinstance()->shaders_.shadowMapVS = shaders;
}

void ShaderManager::SkinningPhongModelShader()
{
	SShaderMode shaders{};
	shaders.vertexBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/SkinningObject3d.VS.hlsl",
			L"vs_6_0");

	shaders.pixelBlob =
		ShaderManager::CompilerShaderFanc(
			L"Resources/Shader/Phong_NormalMap_Model3dObject.PS.hlsl",
			L"ps_6_0");
	ShaderManager::Getinstance()->shaders_.skinningPhongModel = shaders;
}
