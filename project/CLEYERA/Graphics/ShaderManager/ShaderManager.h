#pragma once
#include"Pch.h"
#include"LogManager.h"
struct  SShaderMode
{
	ComPtr<IDxcBlob> vertexBlob;
	ComPtr<IDxcBlob> pixelBlob;
	ComPtr<IDxcBlob>gsBlob;
	ComPtr<IDxcBlob>csBlob;
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
	SShaderMode Line;
	SShaderMode PBR_Model;
	SShaderMode Phong_Normal_Model;
	SShaderMode Phong_Normal_InstancingModel;
	SShaderMode Phong_Dissolve_Model;
 	SShaderMode Phong_subsurface_Model;
	SShaderMode PostEffect;
	SShaderMode skinningPhongModel;
	SShaderMode SkyBoxModel;
};

namespace Shader
{
	enum  Shaders
	{
		SPRITE_2d,
		SPRITE_3d,
		PHONG,
		PARTICLE_INIT,
		PARTICLE_UPDATE,
		PARTICLE_EMITTER,
		PARTICLE_FIELD,
		PARTICLE_DRAW
	};
};

struct  GpuParticleShader
{
	SShaderMode particleInit;
	SShaderMode particleUpdate;
	SShaderMode particleSphereEmitter;
	SShaderMode particleBoxEmitter;
	SShaderMode DebugDraw;
	SShaderMode DissolveDraw;
};

class ShaderManager
{
public:

	static ShaderManager* Getinstance();

	/// <summary>
	/// 初期化　ここで書くシェーダーを作製
	/// </summary>
	static void Initialize();

#pragma region Get
	SShaders GetShader() { return ShaderManager::Getinstance()->shaders_; }
	GpuParticleShader GetParticleShader() { return ShaderManager::Getinstance()->particleShader_; }
	SShaderMode GetShaders(Shader::Shaders shader, string mode) { return shaders[shader][mode]; };
#pragma endregion
private:

	/// <summary>
	/// コンパイル関数
	/// </summary>
	static IDxcBlob* CompilerShaderFanc(
		const std::wstring& filePath,
		const wchar_t* profile
	);

	/// <summary>
	/// dxc作製
	/// </summary>
	static void DxcCreate();

	/// <summary>
	/// include設定
	/// </summary>
	static void includeHandlerSetting();

	/// <summary>
	/// コンパイル実装
	/// </summary>
	static void ShaderComples();

#pragma region 設定したものをshaderComplesで使用

	static void ShapeShader();
	static void Sprite3dShader();
	static void Sprite2dShader();
	static void PBR_ModelShader();
	static void PhongModelShader();
	static void Phong_DissolveShader();
	static void ParticleShader();
	static void PhongNormalModel();
	static void PhongSubsurfaceModel();

	static void PhongNormalInstancingModel();

	static void CreateLineShader();

	static void ColorPostProcess();

	static void PostEffectTest();
	static void ShadowMap();

	static void SkinningPhongModelShader();
	static void SkyBoxModel();

	static void CompileSkinningCs();


	static void Particles();
	static void Particle_Init();
	static void ParticleDebugDraw();
	static void Particle_Update();
	static void Particle_EmitterSphere();
	static void Particle_EmitterBox();

#pragma endregion

	SDXCProperty dxc = {};
	SShaders shaders_ = {};
	GpuParticleShader particleShader_ = {};

	map<Shader::Shaders, map<string, SShaderMode>>shaders;
};

