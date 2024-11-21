#include "PlayerHp.h"

using namespace Engine::Objects;
using namespace Engine::Manager;
using namespace Engine::Transform;

void PlayerHp::Initialize(uint32_t hp)
{
	hpCount_ = hp;

	const float flameOffset = 134.0f;
	const float hpScale = 0.75f;
	const float ankerPoint = -0.5f;

	texHandle_ = TextureManager::LoadDDSTexture("Player/hp/hp.dds");
	Math::Vector::Vector2 texSize = TextureManager::GetTextureSize(texHandle_);
	texSize = Math::Vector::Multiply(texSize, hpScale);
	Math::Vector::Vector2 texPos = Math::Vector::Multiply(texPos, ankerPoint);
	flameTexHandle_ = TextureManager::LoadDDSTexture("Player/hp/HpFlame.dds");
	Math::Vector::Vector2 flameTexSize = TextureManager::GetTextureSize(flameTexHandle_);
	flameNameTexHandle_ = TextureManager::LoadDDSTexture("Player/hp/HpName.dds");
	Math::Vector::Vector2 flameNameTexSize = TextureManager::GetTextureSize(flameNameTexHandle_);

	//hp•\Ž¦
	sprite_ = make_unique<Sprite>();
	sprite_->Initialize();
	sprite_->SetTexHandle(texHandle_);

	wTs_.resize(hpCount_);

	for (size_t i = 0; i < wTs_.size(); i++)
	{
		wTs_[i].Initialize();
		wTs_[i].transform.scale = { hpScale,hpScale,hpScale };
		wTs_[i].transform.translate.x = (texSize.x * i)*1.2f + flameOffset ;
		wTs_[i].transform.translate.y = 10.0f;
	}
	//hpFlame

	flameSprite_ = make_unique<Sprite>();
	flameSprite_->Initialize();
	flameSprite_->SetTexHandle(flameTexHandle_);
	flameWorldTransform_.Initialize();
	flameWorldTransform_.transform.scale = { hpScale,hpScale,hpScale };
	flameWorldTransform_.transform.translate.x += flameOffset;

	flameNameSprite_ = make_unique<Sprite>();
	flameNameSprite_->Initialize();
	flameNameSprite_->SetTexHandle(flameNameTexHandle_);
	flameNameWorldTransform_.Initialize();
	//flameNameWorldTransform_.transform.scale = { hpScale,hpScale,hpScale };
}

void PlayerHp::Update()
{
	for (size_t i = 0; i < wTs_.size(); i++)
	{
		wTs_[i].UpdateMatrix();
	}
	flameWorldTransform_.UpdateMatrix();
	flameNameWorldTransform_.UpdateMatrix();
}

void PlayerHp::ImGuiUpdate()
{
	if (ImGui::TreeNode("hp"))
	{
		if (ImGui::Button("Subtruct"))
		{
			this->hpCount_--;

		}
		ImGui::TreePop();
	}
}

void PlayerHp::Draw2d()
{
	for (int32_t i = 0; i < hpCount_; i++)
	{
		if (i < 0)
		{
			break;
		}
		sprite_->Draw(wTs_[i]);
	}
	//flameNameSprite_->Draw(flameNameWorldTransform_);

	//flameSprite_->Draw(flameWorldTransform_);
}

void PlayerHp::ReduceHp()
{
	hpCount_--;
}
