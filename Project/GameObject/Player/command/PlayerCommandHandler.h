#pragma once
#include"GameObject/Player/Player.h"

#include"PlayerJampCommand.h"
#include"PlayerMoveCommand.h"

class PlayerCommandHandler
{
public:
	PlayerCommandHandler() {};
	~PlayerCommandHandler() {};

	void Handler();

	void CommandCoreExec(Player&p);

private:

	bool IsLJoystickActive();

	queue<unique_ptr<IPlayerCommand>>commands_;

	float joystickThreshold_ = 0.2f;
};