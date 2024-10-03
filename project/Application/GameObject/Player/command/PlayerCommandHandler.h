#pragma once
#include"GameObject/Player/Player.h"

#include"PlayerJampCommand.h"
#include"PlayerMoveCommand.h"
#include"PlayerShootCommand.h"
#include"playerDashMoveCommand.h"

class PlayerCommandHandler
{
public:
	PlayerCommandHandler() {};
	~PlayerCommandHandler() {};

	void Handler();

	void CommandsExec(Player& player);

private:

	bool IsLJoystickActive();

	queue<unique_ptr<IPlayerCommand>>commands_;

	float joystickThreshold_ = 0.2f;
};