#pragma once
#include"Pch.h"
#include"Graphics/TextureManager/TextureManager.h"
#include"CameraData.h"
#include"CreateResource.h"
#include"GraphicsPipelineManager.h"
#include"WorldTransform.h"
#include"Graphics/DescripterManager/RTVDescripterManager.h"
#include"Graphics/DescripterManager/DSVDescriptorManager.h"
#include"CreateResource/BufferResources.h"
#include"Light/DirectionLIght.h"
#include"PostEffectManager.h"

enum SelectPostEffect
{
	GRAYSCALE,
	INVERT,
   BRINGHTNESS,
   CONTRAST,
   HUE,
   AVERAGE_BLUR
};

class PostEffect
{
public:

	static PostEffect* GetInstance();

	void Initialize(const string& name);
	void Update();
	void Draw(const CameraData&view);

	void PreDraw();
	void PostDraw();

	void ShadowMapPreDraw();

	void ShadowMapPostDraw();

#pragma region Set

	void SetPosition(Vector2 pos) { pos_ = pos; }
	void SetSize(Vector2 size) { size_ = size; }

	void SetParam(const PostEffectParam &param) { param_ = param; }
	void SetUvScale(const Vector2 &s) { uvScale_ = { s.x, s.y, 1.0f }; }
	void SetUvRotate(const Vector2 &r) { uvRotate_ = { r .x,r.y,1.0f}; }
	void SetUvTranslate(const Vector2 &t) {uvTranslate_ = { t.x,t.y,1.0f };}
	void SetUvMatrix(const Matrix4x4 &m) { param_.uvMatrix = m; }

	void SetSelectPostEffect(SelectPostEffect s, bool flag);

	/// <summary>
	/// 彩度
	/// </summary>
	void SetGrayFactor(float f) { adjustedColorParam_.GrayFactor = f; }

	/// <summary>
	/// 反転
	/// </summary>
	void SetInvertFactor(float f) { adjustedColorParam_.InvertFactor = f; }

	/// <summary>
	/// 明度
	/// </summary>
	void SetBringhtnessFactor(float f) { adjustedColorParam_.BringhtnessFactor = f; }

	/// <summary>
	/// コントラスト
	/// </summary>
	void SetContrastFactor(const float& f) { adjustedColorParam_.ContrastFactor = f; }

	/// <summary>
	/// 色相
	/// </summary>
	void SetHueFactor(const float& f) { adjustedColorParam_.HueFactor = f; }
	
	/// <summary>
	/// 平均ぼかしの強さ
	/// </summary>
	void SetBlurintensity(float f) { blurParam_.Intensity = f; }

#pragma endregion

private:

	void CommandCallView(const float& width, const float& height);
	void CommandCallScissor();

	void CreateTexBuffer();
	void TransfarImage();
	void AddSRVDescripter();

	void CreateRTV();
	void CreateDSV();
	void CreateShadowMap();
	void CreateShadowMapResource();
	void CreateShadowMapDSV();
	void CreateShadowMapSRV();

	void CreateBloom();
	void CreateBloomBuffer();
	void CreateBloomRTV();
	void CreateBloomSRV();

	Vector2 pos_ = {};
	Vector2 size_ = { static_cast<float>(WinApp::GetkCilientWidth()), static_cast<float>(WinApp::GetkCilientHeight())};

	uint32_t srvIndex_ = 0;
	uint32_t rtvIndex_ = 0;
	uint32_t dsvIndex_ = 0;
	uint32_t srvShadowIndex_ = 0;
	uint32_t dsvShadowIndex_ = 0;
	uint32_t 	rtvshadowIndex_ = 0;
	const float clearColor[4] = { 0.25f,0.5f,0.1f,0.0f };

	ComPtr<ID3D12Resource>texBuffer_ = nullptr;
	ComPtr<ID3D12Resource>depthBuffer_ = nullptr;
	ComPtr<ID3D12Resource>depthNormalBuffer_ = nullptr;
	const static uint32_t BloomNum_ = 2;

	std::array<ComPtr<ID3D12Resource>, BloomNum_>BloomBuffer_ = {};

	unique_ptr<BufferResource<VertexData>>vertexBuffer_ = nullptr;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_ = {};

	unique_ptr<BufferResource<TransformationMatrix>>wvp_ = nullptr;

	unique_ptr<BufferResource<PostEffectParam>>paramBuffer_ = nullptr;
	unique_ptr<BufferResource<PostEffectBlurParam>>blurParamBuffer_ = nullptr;
	unique_ptr<BufferResource<PostEffectAdjustedColorParam>> adjustedColorBuffer_ = nullptr;

	PostEffectBlurParam blurParam_ = {};
	PostEffectParam param_ = {};
	PostEffectAdjustedColorParam adjustedColorParam_ = {};
	Vector3 uvScale_ = {1.0f,1.0f,1.0f};
	Vector3 uvRotate_ = {};
	Vector3 uvTranslate_ = {};

};
