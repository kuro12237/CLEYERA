#include "PlayerHp.h"

void PlayerHp::Initialize(uint32_t hp)
{
	hpCount_ = hp;
	texHandle_ = TextureManager::LoadDDSTexture("Player/hp/hp.dds");
	Math::Vector::Vector2 texSize = TextureManager::GetTextureSize(texHandle_);

	Math::Vector::Vector2 texPos = { texSize.x * -0.5f, texSize.y * -0.5f };

	sprite_ = make_unique<Sprite>();
	sprite_->Initialize(texPos);
	sprite_->SetTexHandle(texHandle_);

	wTs_.resize(hpCount_);
	float kScale = 1.0f / 16.0f;

	for (size_t i = 0; i < wTs_.size(); i++)
	{
		wTs_[i].Initialize();
		wTs_[i].transform.scale = { kScale,kScale,kScale };
		wTs_[i].transform.translate.x = (texSize.x * i) * kScale + (texSize.x*kScale)/ 2.0f;
	}
}

void PlayerHp::Update()
{
	for (size_t i = 0; i < wTs_.size(); i++)
	{
		wTs_[i].UpdateMatrix();
	}
}

void PlayerHp::Draw2d()
{
	for (size_t i = 0; i < hpCount_; i++)
	{
		sprite_->Draw(wTs_[i]);
	}
}
