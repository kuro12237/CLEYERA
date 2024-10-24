#pragma once
#include"Pch.h"
#include"WorldTransform.h"
#include"GraphicsPipelineManager.h"
#include"Graphics/DescripterManager/DescriptorManager.h"
#include"ISpriteBuf.h"

#include"Utility/CameraManager/CameraManager.h"
#include"Graphics/TextureManager/TextureManager.h"

namespace Engine::Objects
{
	class Sprite :public System::ISpriteBuf
	{
	public:
		Sprite() {};
		~Sprite() {  };
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="どこを中心にするか"></param>
		/// <param name="画像サイズ:texを使用する場合使用しない"></param>
		void Initialize(Math::Vector::Vector2 pos = {}, Math::Vector::Vector2 size = {});

		/// <summary>
		/// 表示
		/// </summary>
		/// <param name="worldTransform"></param>
		void Draw(Engine::Transform::WorldTransform worldTransform);

#pragma region Set
		void SetTexHandle(uint32_t texHandle);
		void SetNoiseTex(uint32_t tex) { noiseTexHandle_ = tex; }
		void SetUvScale(Math::Vector::Vector3 uvScale) { uvScale_ = uvScale; }
		void SetUvRotate(Math::Vector::Vector3 uvRotate) { uvRotate_ = uvRotate; }
		void SetUvTranslate(Math::Vector::Vector3 uvTranslate) { uvTranslate_ = uvTranslate; }
		void SetColor(Math::Vector::Vector4 color) { color_ = color; }

		/// <summary>
		/// ブレンド
		/// </summary>
		void SetSpriteMode(SpriteMode blendMode) { blendMode_ = blendMode; }

		void SetSize(Math::Vector::Vector2 size) { size_ = size; }

		/// <summary>
		/// tex切り抜き
		/// </summary>
		/// <param name="左上"></param>
		/// <param name="左下"></param>
		/// <param name="右上"></param>
		/// <param name="右下"></param>
		void SetSrc(Math::Vector::Vector2 TL, Math::Vector::Vector2 BL, Math::Vector::Vector2 TR, Math::Vector::Vector2 BR);

#pragma endregion 

#pragma region get
		Math::Vector::Vector4 GetColor() { return color_; }
		uint32_t GetTexHandle() { return texHandle_; }

		Math::Vector::Vector3& GetuvScale() { return uvScale_; }
		Math::Vector::Vector3& GetuvRotate() { return uvRotate_; }
		Math::Vector::Vector3& GetuvTranslate() { return uvTranslate_; }

		Math::Vector::Vector3& GetNoiseUvScale() { return noiseUvScale_; }
		const Math::Vector::Vector3& GetNoiseUvRotate() { return noiseUvRotate_; }
		Math::Vector::Vector3& GetNoiseUvTranslate() { return noiseUvTranslate_; }

		float& GetPerlinNoiseScale() { return PerlinNoiseScale_; }
		float& GetPerlinNoiseFactor() { return perlinNoiseFactor_; }
		Math::Vector::Vector2& GetPerlinNoisePos() { return perlinNoisePos_; }
		float& GetPerlinNoiseTimer() { return perlinNoiseTimer_; }

		SpriteMode GetSpriteMode() { return blendMode_; }

		Math::Vector::Vector2& GetPos() { return pos_; }
		Math::Vector::Vector2 GetSize() { return size_; }

		Math::Vector::Vector2 GetSrcTR() { return srcTR; }
		Math::Vector::Vector2 GetSrcBR() { return srcBR; }
		Math::Vector::Vector2 GetSrcTL() { return srcTL; }
		Math::Vector::Vector2 GetSrcBL() { return srcBL; }

		float& GetDissolveMask() { return dissolveMask_; }
		Math::Vector::Vector2& GetDissolveEdgeMinMax() { return dissolveEdgeMinMax_; }
		Math::Vector::Vector4& GetDissolveDdgeColor() { return dissolveEdgeColor_; }

#pragma endregion

	private:

		SPSOProperty Get2dSpritePipeline(Sprite* state);

		void CommandCall(const Engine::Transform::WorldTransform& worldTransform);

		Math::Vector::Vector2 pos_ = { 0,0 };
		Math::Vector::Vector2 size_ = {};
		Math::Vector::Vector4 color_ = { 1,1,1,1 };

		uint32_t texHandle_ = 0;
		uint32_t noiseTexHandle_ = 0;

		float dissolveMask_ = 0.0f;
		Math::Vector::Vector2 dissolveEdgeMinMax_ = {};
		Math::Vector::Vector4 dissolveEdgeColor_ = { 1.0f,1.0f,1.0f,1.0f };

		Math::Vector::Vector3 uvScale_ = { 1,1,1 };
		Math::Vector::Vector3 uvRotate_ = { 0,0,0 };
		Math::Vector::Vector3 uvTranslate_ = { 0,0,0 };

		Math::Vector::Vector3 noiseUvScale_ = { 1,1,1 };
		Math::Vector::Vector3 noiseUvRotate_ = { 0,0,0 };
		Math::Vector::Vector3 noiseUvTranslate_ = { 0,0,0 };

		float perlinNoiseTimer_ = 0.0f;

		float PerlinNoiseScale_ = 0;
		float perlinNoiseFactor_ = 0;
		Math::Vector::Vector2 perlinNoisePos_ = {};

		Math::Vector::Vector2 srcTR = { 1.0f,0.0f };
		Math::Vector::Vector2 srcBR = { 1.0f,1.0f };
		Math::Vector::Vector2 srcTL = { 0.0f,0.0f };
		Math::Vector::Vector2 srcBL = { 0.0f,1.0f };

		SpriteMode blendMode_ = BlendNone;

	};
}