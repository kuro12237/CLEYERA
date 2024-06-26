#include "PlayerManager.h"

void PlayerManager::GetData(GameObjectManager* data)
{
	playerCore_ = make_shared<Player>();
	playerCore_->Initialize();
	playerCore_->GetData(data);

	commandHandler_ = make_unique<PlayerCommandHandler>();
	reticleCommandHandler_ = make_unique<PlayerReticleCommandHandler>();

	reticle_ = make_unique<PlayerReticle>();
	reticle_->Initialize();

	gun_ = make_unique<PlayerGun>();
	gun_->Initialize();
}

void PlayerManager::ImGuiUpdate()
{
	playerCore_->ImGuiUpdate();
	reticle_->ImGuiUpdate();
	gun_->Update();
}

void PlayerManager::Update()
{
	GameObjectManager* instance = GameObjectManager::GetInstance();
	Math::Vector::Vector3 playerWorldPos, reticleWorldPos;
	reticleWorldPos = instance->GetObj3dData(reticle_->GetName()).worldTransform.GetWorldPosition();
	playerWorldPos = instance->GetObj3dData(playerCore_->GetName()).worldTransform.GetWorldPosition();

	gun_->SetTarget(reticleWorldPos);

	reticleCommandHandler_->Handler();
	reticleCommandHandler_->Exec(*reticle_);
	reticle_->Update();

	commandHandler_->Handler();
	commandHandler_->CommandCoreExec(*playerCore_);
	playerCore_->Update();
}

void PlayerManager::PushBullet(Math::Vector::Vector3 pos)
{
	pos;
	unique_ptr<PlayerBullet> b = make_unique<PlayerBullet>();
	b->Initialize();
	if (!deadBulletIndex_.empty())
	{
		uint32_t newBulletIndex = deadBulletIndex_.front();
		bullets_[newBulletIndex] = move(b);
		deadBulletIndex_.pop();
	}
	else
	{
		bullets_.push_back(move(b));
	}

}
