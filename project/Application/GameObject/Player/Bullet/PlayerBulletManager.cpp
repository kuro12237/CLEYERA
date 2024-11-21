#include "PlayerBulletManager.h"

using namespace Engine::Objects;

using namespace Engine;
using namespace Engine::Manager;
using namespace Engine::Transform;

void PlayerBulletManager::Initialize()
{
	texHandle_ = TextureManager::LoadPngTexture("BulletUI/bullet.png");

	bulletSprite_ = make_unique<Sprite>();
	bulletSprite_->Initialize();
	bulletSprite_->SetTexHandle(texHandle_);

	worldTransforms_.resize(bulletCountMax_);

	const float kScale = 0.075f;
	const Math::Vector::Vector2 texSize = TextureManager::GetTextureSize(texHandle_);
	Math::Vector::Vector2 pos = { 96.0f,64.0f };
	for (size_t i = 0; i < bulletCountMax_; i++)
	{
		worldTransforms_[i].Initialize();
		worldTransforms_[i].transform.scale = { kScale,kScale,kScale };
		
		worldTransforms_[i].transform.translate.x += texSize.x * kScale * float(i) + pos.x;
		worldTransforms_[i].transform.translate.y = pos.y;
	}

}

void PlayerBulletManager::ImGuiUpdate()
{
	if (ImGui::TreeNode("bulletManager"))
	{
		ImGui::Text("bulletCount:%d", int(bulletCount_));
		ImGui::Text("delta::%d", int(deltaCount_));

		ImGui::TreePop();
	}

}

void PlayerBulletManager::Update()
{
	if (bulletCountMax_ - bulletCount_ != bulletCountMax_)
	{
		deltaCount_ += DeltaTimer(flame_);
	}

	if (bulletCount_ >= 1)
	{
		if (deltaCount_ >= 2)
		{
			deltaCount_ = 0;
			bulletCount_--;
		}
	}

	for (Engine::Transform::WorldTransform& wt : worldTransforms_)
	{
		wt.UpdateMatrix();
	}
}

void PlayerBulletManager::Draw2d()
{
	uint32_t max = bulletCountMax_ - bulletCount_;
	for (size_t i = 0; i < max; i++)
	{
		bulletSprite_->Draw(worldTransforms_[i]);
	}
}
