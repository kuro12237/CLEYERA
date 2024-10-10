#include "TitleName.h"

void TitleName::Initialize()
{
	texHandle_ = TextureManager::LoadPngTexture("Title/titleName.png");
	sprite_ = make_unique<Sprite>();
	sprite_->Initialize();
	sprite_->SetTexHandle(texHandle_);

	worldTransform_.Initialize();

}

void TitleName::Update()
{
	worldTransform_.UpdateMatrix();
}

void TitleName::Draw()
{
	sprite_->Draw(worldTransform_);
}
