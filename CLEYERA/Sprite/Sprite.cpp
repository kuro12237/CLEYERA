#include "Sprite.h"

void Sprite::Initialize(ISpriteState* state, Vector2 pos, Vector2 size)
{
	state_ = state;
	state_->Initialize(this);

	Pos_ = pos;
	if (size.x == 0 && size.y == 0)
	{
		size_ = TextureManager::GetTextureSize(texHandle_);
	}
	else
	{
		size_ = size;
	}
	blendMode_ = BlendNone;
}

void Sprite::Draw(WorldTransform worldTransform, CameraData  view)
{
	state_->Draw(this, worldTransform,view);
}

void Sprite::SetTexHandle(uint32_t texHandle)
{
	texHandle_ = texHandle;
	size_ = TextureManager::GetTextureSize(texHandle);
}

void Sprite::SetSrc(Vector2 TL, Vector2 BL,Vector2 TR, Vector2 BR)
{
	srcTR = TR;
	srcBR = BR;
	srcTL = TL;
	srcBL = BL;
}

Vector4 Sprite::ColorConversion(uint32_t rgbaValue)
{
	Vector4 result = {};
	result.x = ((rgbaValue >> 24) & 0xFF) / 255.0f; // Red
	result.y = ((rgbaValue >> 16) & 0xFF) / 255.0f; // Green
	result.z = ((rgbaValue >> 8) & 0xFF) / 255.0f;  // Blue
	result.w = (rgbaValue & 0xFF) / 255.0f;         // Alpha
	return result;
}

