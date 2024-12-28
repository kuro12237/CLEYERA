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
		PBR,
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

	/// <summary>
/// シェイプ用のシェーダーをコンパイルする関数
/// </summary>
	static void ShapeShader();

	/// <summary>
	/// 3Dスプライト用のシェーダーをコンパイルする関数
	/// </summary>
	static void Sprite3dShader();

	/// <summary>
	/// 2Dスプライト用のシェーダーをコンパイルする関数
	/// </summary>
	static void Sprite2dShader();

	/// <summary>
	/// PBR（物理ベースレンダリング）モデル用のシェーダーをコンパイルする関数
	/// </summary>
	static void PBR_ModelShader();

	/// <summary>
	/// フォンモデル用のシェーダーをコンパイルする関数
	/// </summary>
	static void PhongModelShader();

	/// <summary>
	/// フォンモデル用のディゾルブシェーダーをコンパイルする関数
	/// </summary>
	static void Phong_DissolveShader();

	/// <summary>
	/// パーティクル用のシェーダーをコンパイルする関数
	/// </summary>
	static void ParticleShader();

	/// <summary>
	/// フォンモデルの法線マップを使用したシェーダーをコンパイルする関数
	/// </summary>
	static void PhongNormalModel();

	/// <summary>
	/// サブサーフェススキャッタリングを使用したフォンモデル用のシェーダーをコンパイルする関数
	/// </summary>
	static void PhongSubsurfaceModel();

	/// <summary>
	/// インスタンシングを使用したフォンモデルの法線シェーダーをコンパイルする関数
	/// </summary>
	static void PhongNormalInstancingModel();

	/// <summary>
	/// ライン描画用のシェーダーをコンパイルする関数
	/// </summary>
	static void CreateLineShader();

	/// <summary>
	/// カラーポストプロセス用のシェーダーをコンパイルする関数
	/// </summary>
	static void ColorPostProcess();

	/// <summary>
	/// ポストエフェクトテスト用のシェーダーをコンパイルする関数
	/// </summary>
	static void PostEffectTest();

	/// <summary>
	/// シャドウマップ用のシェーダーをコンパイルする関数
	/// </summary>
	static void ShadowMap();

	/// <summary>
	/// スキニングを使用したフォンモデル用のシェーダーをコンパイルする関数
	/// </summary>
	static void SkinningPhongModelShader();

	/// <summary>
	/// スカイボックス描画用のシェーダーをコンパイルする関数
	/// </summary>
	static void SkyBoxModel();

	/// <summary>
	/// スキニングのコンピュートシェーダーをコンパイルする関数
	/// </summary>
	static void CompileSkinningCs();

	/// <summary>
	/// パーティクルシェーダーをコンパイルする関数
	/// </summary>
	static void Particles();

	/// <summary>
	/// パーティクルの初期化用シェーダーをコンパイルする関数
	/// </summary>
	static void Particle_Init();

	/// <summary>
	/// パーティクルデバッグ描画用のシェーダーをコンパイルする関数
	/// </summary>
	static void ParticleDebugDraw();

	/// <summary>
	/// パーティクルの更新用シェーダーをコンパイルする関数
	/// </summary>
	static void Particle_Update();

	/// <summary>
	/// 球形エミッタ用のパーティクルシェーダーをコンパイルする関数
	/// </summary>
	static void Particle_EmitterSphere();

	/// <summary>
	/// ボックス形エミッタ用のパーティクルシェーダーをコンパイルする関数
	/// </summary>
	static void Particle_EmitterBox();


#pragma endregion

	SDXCProperty dxc = {};
	SShaders shaders_ = {};
	GpuParticleShader particleShader_ = {};

	map<Shader::Shaders, map<string, SShaderMode>>shaders;
};

