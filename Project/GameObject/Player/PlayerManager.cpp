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
}

void PlayerManager::ImGuiUpdate()
{
	playerCore_->ImGuiUpdate();
	reticle_->ImGuiUpdate();
}

void PlayerManager::Update()
{
	reticleCommandHandler_->Handler();
	reticleCommandHandler_->Exec(*reticle_);
	reticle_->Update();

	commandHandler_->Handler();
	commandHandler_->CommandCoreExec(*playerCore_);
	playerCore_->Update();
}
