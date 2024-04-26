#pragma once
#include"GameObject/Player/Commands/IPlayerCommand.h"
#include"Input.h"
#include"GameObject/Player/Commands/PlayerJampCommand.h"
#include"GameObject/Player/Commands/PlayerGunAttackCommand.h"

class PlayerInputHandler
{
public:
	PlayerInputHandler() {};
	~PlayerInputHandler() {};

	void Handler();

	void CommandsExc(Player& player);

	void ImGuiUpdate();

private:

	std::queue<unique_ptr<IPlayerCommand>>commands_{};

};