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
#include"Utility/CameraManager/CameraManager.h"

enum SelectPostEffect
{
	GRAYSCALE,
	INVERT,
   BRINGHTNESS,
   CONTRAST,
   HUE,
   AVERAGE_BLUR,
   VIGNETTE
};

class PostEffect
{
public:

	static PostEffect* GetInstance();

	void Initialize();
	void Update();
	void Draw();

	void PreDraw();
	void PostDraw();

#pragma region Set

	void SetPosition(Math::Vector::Vector2 pos) { pos_ = pos; }
	void SetSize(Math::Vector::Vector2 size) { size_ = size; }

	void SetParam(const PostEffectParam &param) { param_ = param; }
	void SetUvScale(const Math::Vector::Vector2 &s) { uvScale_ = { s.x, s.y, 1.0f }; }
	void SetUvRotate(const Math::Vector::Vector2 &r) { uvRotate_ = { r .x,r.y,1.0f}; }
	void SetUvTranslate(const Math::Vector::Vector2 &t) {uvTranslate_ = { t.x,t.y,1.0f };}
	void SetUvMatrix(const Math::Matrix::Matrix4x4 &m) { param_.uvMatrix = m; }

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

	void SetVignetteFactor(float f) { adjustedColorParam_.vignetteFactor = f; }

	void SetVignetteColor(Math::Vector::Vector3 color) { adjustedColorParam_.viganetteColor_ = color;}

	void SetVignetteScale(float s) { adjustedColorParam_.vignetteScale = s; }

#pragma endregion

private:

	void CommandCallView(const float& width, const float& height);
	void CommandCallScissor();

	bool isInitialize_ = false;

	Math::Vector::Vector2 pos_ = {};
	Math::Vector::Vector2 size_ = { static_cast<float>(Engine::Base::Win::WinApp::GetkCilientWidth()), static_cast<float>(Engine::Base::Win::WinApp::GetkCilientHeight())};

	const float clearColor[4] = { 0.25f,0.5f,0.1f,0.0f };

	unique_ptr<BufferResource<uint32_t>>albedBuf_ = nullptr;
	unique_ptr<BufferResource<uint32_t>>texBuf_ = nullptr;
	unique_ptr<BufferResource<uint32_t>>depthTexBuffer_ = nullptr;
	unique_ptr<BufferResource<uint32_t>>outLineColor_ = nullptr;

	unique_ptr<BufferResource<TransformationMatrix>>wvp_ = nullptr;

	unique_ptr<BufferResource<PostEffectParam>>paramBuffer_ = nullptr;
	unique_ptr<BufferResource<PostEffectBlurParam>>blurParamBuffer_ = nullptr;
	unique_ptr<BufferResource<PostEffectAdjustedColorParam>> adjustedColorBuffer_ = nullptr;

	PostEffectBlurParam blurParam_ = {};
	PostEffectParam param_ = {};
	PostEffectAdjustedColorParam adjustedColorParam_ = {};
	Math::Vector::Vector3 uvScale_ = {1.0f,1.0f,1.0f};
	Math::Vector::Vector3 uvRotate_ = {};
	Math::Vector::Vector3 uvTranslate_ = {};

};
