#pragma once
#include"GameObject/ObjectManager/GameObjectManager.h"
#include"Player.h"
#include"Reticle/PlayerReticle.h"

#include"command/PlayerCommandHandler.h"
#include"Reticle/command/PlayerReticleCommandHandler.h"

class PlayerManager
{
public:
	PlayerManager() {};
	~PlayerManager() {};

	void GetData(GameObjectManager* data);

	void ImGuiUpdate();

	void Update();

#pragma region Get

	Player* GetPlayerCore() { return playerCore_.get(); }

	PlayerReticle* GetReticle() { return reticle_.get(); }

#pragma endregion

private:

	unique_ptr<PlayerCommandHandler>commandHandler_ = nullptr;
	unique_ptr<PlayerReticleCommandHandler>reticleCommandHandler_ = nullptr;

	shared_ptr<Player>playerCore_ = nullptr;
	unique_ptr<PlayerReticle>reticle_ = nullptr;

};