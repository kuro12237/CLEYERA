#include "PlayerHp.h"

void PlayerHp::Initialize()
{
	sprite_ = std::make_unique<Sprite>();
	sprite_->Initialize(new SpriteBoxState);

	spriteHandle_ = TextureManager::LoadPngTexture("uvChecker.png");
	sprite_->SetTexHandle(spriteHandle_);

	for (uint32_t i = 0; i < playerHpMax_; i++)
	{
		WorldTransform w = {};
		w.Initialize();
		w.translate.x = float(32 * i);
		worldTransform_[i] = w;
	}

	playerHpCount_ = playerHpMax_;
}

void PlayerHp::Update()
{
	if (coolTimer_ < coolTimerMax_)
	{
		coolTimer_ += DeltaTimer(flame_);
	}

	for (uint32_t i = 0; i < playerHpCount_; i++)
	{
		worldTransform_[i].UpdateMatrix();
	}
}

void PlayerHp::Draw2d(const CameraData& camera)
{

	for (uint32_t i = 0; i < playerHpCount_; i++)
	{
		sprite_->Draw(worldTransform_[i], camera);
	}
}

void PlayerHp::subtractHPCount(uint32_t param)
{
	if (coolTimer_ >= coolTimerMax_)
	{
		if (playerHpCount_ == 0)
		{
			//HPが0の時にエラー
			assert(0);
		}
		playerHpCount_ -= param;
		coolTimer_ = 0;
	}
}

void PlayerHp::ImGuiUpdate()
{
	if (ImGui::Button("subtructHp"))
	{
		subtractHPCount(1);
	}
}
