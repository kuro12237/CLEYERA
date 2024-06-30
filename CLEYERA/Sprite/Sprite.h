#pragma once
#include"Pch.h"
#include"WorldTransform.h"
#include"Sprite/state/SpriteBoxState.h"
#include"GraphicsPipelineManager.h"

class Sprite
{
public:
	Sprite() {};
	~Sprite() { delete state_; };

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="表示方法"></param>
	/// <param name="どこから表示するか"></param>
	/// <param name="画像サイズ:texを使用する場合使用しない"></param>
	void Initialize(ISpriteState* state, Math::Vector::Vector2 pos = {}, Math::Vector::Vector2 size = {});

	void Draw(WorldTransform worldTransform);

#pragma region Set
	void SetTexHandle(uint32_t texHandle);
	void SetUvScale(Math::Vector::Vector3 uvScale) { uvScale_ = uvScale; }
	void SetUvRotate(Math::Vector::Vector3 uvRotate) { uvRotate_ = uvRotate; }
	void SetUvTranslate(Math::Vector::Vector3 uvTranslate) { uvTranslate_ = uvTranslate; }
	void SetColor(Math::Vector::Vector4 color) { color_ = color; }
	
	/// <summary>
	/// ブレンド
	/// </summary>
	void SetBlendMode(BlendMode blendMode) { blendMode_ = blendMode; }
	
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

	Math::Vector::Vector3 GetuvScale() { return uvScale_; }
	Math::Vector::Vector3 GetuvRotate() { return uvRotate_; }
	Math::Vector::Vector3 GetuvTranslate() { return uvTranslate_; }
	BlendMode GetBlendMode() {return blendMode_; }

	/// <summary>
	/// GetSpritePos
	/// </summary>
	Math::Vector::Vector2 GetPos() { return Pos_; }
	/// <summary>
	/// GetSpriteSize
	/// </summary>
	Math::Vector::Vector2 GetSize() { return size_; }

	/// <summary>
	/// color16からvec4へ
	/// </summary>
	static Math::Vector::Vector4 ColorConversion(uint32_t rgbaValue);

	Math::Vector::Vector2 GetSrcTR() { return srcTR; }
	Math::Vector::Vector2 GetSrcBR() { return srcBR; }
	Math::Vector::Vector2 GetSrcTL() { return srcTL; }
	Math::Vector::Vector2 GetSrcBL() { return srcBL; }

#pragma endregion

private:
	Math::Vector::Vector2 Pos_ = { 0,0 };
	Math::Vector::Vector2 size_ = {};
	Math::Vector::Vector4 color_ = { 1,1,1,1 };

	uint32_t texHandle_ = 0;

	Math::Vector::Vector3 uvScale_ = { 1,1,1 };
	Math::Vector::Vector3 uvRotate_ = { 0,0,0 };
	Math::Vector::Vector3 uvTranslate_ = { 0,0,0 };

	Math::Vector::Vector2 srcTR = { 1.0f,0.0f };
	Math::Vector::Vector2 srcBR = { 1.0f,1.0f };
	Math::Vector::Vector2 srcTL = { 0.0f,0.0f };
	Math::Vector::Vector2 srcBL = { 0.0f,1.0f };

	BlendMode blendMode_= BlendNone;
	ISpriteState* state_ = {};
};


