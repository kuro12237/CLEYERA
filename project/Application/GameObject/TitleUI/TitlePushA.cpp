#include "TitlePushA.h"

void TitlePushA::Initiaize()
{
	texhandle_ = TextureManager::LoadPngTexture("Title/Push_A.png");
	Math::Vector::Vector2 texSize = TextureManager::GetTextureSize(texhandle_);
	Math::Vector::Vector2 texPos = TextureManager::CalcAnkerPos(texSize);

	sprite_ = make_unique<Sprite>();
	sprite_->Initialize(texPos);
	sprite_->SetTexHandle(texhandle_);

	worldTransform_.Initialize();
	worldTransform_.transform.scale = { kScale_,kScale_};
	worldTransform_.transform.translate = pos_;


}

void TitlePushA::Update()
{
	worldTransform_.UpdateMatrix();
}

void TitlePushA::Draw()
{
	sprite_->Draw(worldTransform_);
}
