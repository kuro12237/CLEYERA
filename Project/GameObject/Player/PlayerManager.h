#pragma once
#include"GameObject/ObjectManager/GameObjectManager.h"
#include"Player.h"
#include"command/PlayerCommandHandler.h"

class PlayerManager
{
public:
	PlayerManager() {};
	~PlayerManager() {};

	void GetData(GameObjectManager* data);

	void Update();

#pragma region Get

	Player* GetPlayerCore() { return playerCore_.get(); }

#pragma endregion

private:

	unique_ptr<PlayerCommandHandler>commandHandler_ = nullptr;

	shared_ptr<Player>playerCore_ = nullptr;

};