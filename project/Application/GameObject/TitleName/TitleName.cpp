#include "TitleName.h"


using namespace Engine::Base::DX;
using namespace Engine::Base::Win;
using namespace Engine::Transform;
using namespace Engine::Objects;

using namespace Engine::Manager;

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
