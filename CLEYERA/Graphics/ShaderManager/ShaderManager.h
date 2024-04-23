#pragma once
#include"Pch.h"
#include"LogManager.h"
struct  SShaderMode
{
	ComPtr<IDxcBlob> vertexBlob;
	ComPtr<IDxcBlob> pixelBlob;
};
struct SDXCProperty
{
	ComPtr<IDxcIncludeHandler>m_pIncludeHandler;
	ComPtr<IDxcUtils> m_pUtils;
	ComPtr<IDxcCompiler3> m_pCompiler;
};

struct SShaders
{
	SShaderMode shape;
	SShaderMode sprite3d;
	SShaderMode sprite2d;
	SShaderMode PBR_Model;
	SShaderMode Phong_Model;
	SShaderMode Phong_Normal_Model;
	SShaderMode Phong_Normal_InstancingModel;
	SShaderMode Phong_subsurface_Model;
	SShaderMode Particle;
	SShaderMode LightParticle;
	SShaderMode PostEffectTest;
	SShaderMode shadowMapVS;
	SShaderMode ColorModel;
	SShaderMode NormalModel;
	SShaderMode PosModel;
	SShaderMode ColorPostProcess;
};

class ShaderManager
{
public:

	static ShaderManager* Getinstance();

	static void Initialize();

#pragma region Get
	SShaders GetShader() { return ShaderManager::Getinstance()->shaders_; }

#pragma endregion
private:

	/// <summary>
	/// �V�F�[�_�[�̃R���p�C���֐�
	/// </summary>
	static IDxcBlob* CompilerShaderFanc(
		const std::wstring& filePath,
		const wchar_t* profile
	);

	static void DxcCreate();
	static void includeHandlerSetting();

	static void ShaderComples();

	static void ShapeShader();
	static void Sprite3dShader();
	static void Sprite2dShader();
	static void PBR_ModelShader();
	static void PhongModelShader();
	static void ParticleShader();
	static void PhongNormalModel();
	static void PhongSubsurfaceModel();

	static void PhongNormalInstancingModel();


	static void ColorModel();
	static void NormalModel();
	static void PosModel();
	static void ColorPostProcess();

	static void PostEffectTest();
	static void ShadowMap();

	SDXCProperty dxc = {};
	SShaders shaders_ = {};

};

