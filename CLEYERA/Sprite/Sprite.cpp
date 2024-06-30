#include "Sprite.h"

using namespace Math::Vector;

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

void Sprite::Draw(WorldTransform worldTransform)
{
	state_->Draw(this, worldTransform);
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



