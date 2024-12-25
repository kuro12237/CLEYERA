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


namespace Engine
{



	/// <summary>
	/// ポストエフェクトクラス
	/// </summary>
	class PostEffect
	{
	public:

		static PostEffect* GetInstance();

		void Initialize();
		void Update();
		void Draw();

		/// <summary>
		/// 使用しない
		/// </summary>
		void PreDraw();

		/// <summary>
		/// 使用しない
		/// </summary>
		void PostDraw();

#pragma region Get

		bool GetIsUseVinatte() { return adjustedColorParam_.vignetteFlag; }

		PostEffectAdjustedColorParam &GetAdjustedColorParam() { return adjustedColorParam_; }
#pragma endregion

#pragma region Set
		void SetPosition(Math::Vector::Vector2 pos) { pos_ = pos; }
		void SetSize(Math::Vector::Vector2 size) { size_ = size; }
		void SetParam(const PostEffectParam& param) { param_ = param; }
		void SetUvScale(const Math::Vector::Vector2& s) { uvScale_ = { s.x, s.y, 1.0f }; }
		void SetUvRotate(const Math::Vector::Vector2& r) { uvRotate_ = { r.x,r.y,1.0f }; }
		void SetUvTranslate(const Math::Vector::Vector2& t) { uvTranslate_ = { t.x,t.y,1.0f }; }
		void SetUvMatrix(const Math::Matrix::Matrix4x4& m) { param_.uvMatrix = m; }

		void SetSelectPostEffect(SelectPostEffect s, bool flag);
		void SetGrayFactor(float f) { adjustedColorParam_.GrayFactor = f; }
		void SetInvertFactor(float f) { adjustedColorParam_.InvertFactor = f; }
		void SetBringhtnessFactor(float f) { adjustedColorParam_.BringhtnessFactor = f; }
		void SetContrastFactor(const float& f) { adjustedColorParam_.ContrastFactor = f; }
		void SetHueFactor(const float& f) { adjustedColorParam_.HueFactor = f; }
		void SetBlurintensity(float f) { blurParam_.Intensity = f; }
		void SetVignetteFactor(float f) { adjustedColorParam_.vignetteFactor = f; }
		void SetVignetteColor(Math::Vector::Vector3 color) { adjustedColorParam_.viganetteColor_ = color; }
		void SetVignetteScale(float s) { adjustedColorParam_.vignetteScale = s; }
#pragma endregion

	private:

		/// <summary>
		/// viewのコマンドを積む
		/// </summary>
		/// <param name="width"></param>
		/// <param name="height"></param>
		void CommandCallView(const float& width, const float& height);

		/// <summary>
		/// シザーのコマンドを積む
		/// </summary>
		void CommandCallScissor();

		bool isInitialize_ = false;

		Math::Vector::Vector2 pos_ = {};
		Math::Vector::Vector2 size_ = { static_cast<float>(Engine::Base::Win::WinApp::GetkCilientWidth()), static_cast<float>(Engine::Base::Win::WinApp::GetkCilientHeight()) };

		const float clearColor[4] = { 0.25f,0.5f,0.1f,0.0f };

		unique_ptr<Engine::Buffer::BufferResource<uint32_t>>albedBuf_ = nullptr;
		unique_ptr<Engine::Buffer::BufferResource<uint32_t>>texBuf_ = nullptr;
		unique_ptr<Engine::Buffer::BufferResource<uint32_t>>depthTexBuffer_ = nullptr;
		unique_ptr<Engine::Buffer::BufferResource<uint32_t>>outLineColor_ = nullptr;

		unique_ptr<Engine::Buffer::BufferResource<TransformationMatrix>>wvp_ = nullptr;

		unique_ptr<Engine::Buffer::BufferResource<PostEffectParam>>paramBuffer_ = nullptr;
		unique_ptr<Engine::Buffer::BufferResource<PostEffectBlurParam>>blurParamBuffer_ = nullptr;
		unique_ptr<Engine::Buffer::BufferResource<PostEffectAdjustedColorParam>> adjustedColorBuffer_ = nullptr;

		PostEffectBlurParam blurParam_ = {};
		PostEffectParam param_ = {};
		PostEffectAdjustedColorParam adjustedColorParam_ = {};
		Math::Vector::Vector3 uvScale_ = { 1.0f,1.0f,1.0f };
		Math::Vector::Vector3 uvRotate_ = {};
		Math::Vector::Vector3 uvTranslate_ = {};

	};

}