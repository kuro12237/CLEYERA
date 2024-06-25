#include "PlayerManager.h"

void PlayerManager::GetData(GameObjectManager* data)
{
	playerCore_ = make_shared<Player>();
	playerCore_->Initialize();
	playerCore_->GetData(data);

	commandHandler_ = make_unique<PlayerCommandHandler>();
}

void PlayerManager::Update()
{
	commandHandler_->Handler();
	commandHandler_->CommandExec(*playerCore_);

	playerCore_->Update();
}
