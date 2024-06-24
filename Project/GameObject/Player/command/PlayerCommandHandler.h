#pragma once
#include"GameObject/Player/Player.h"
#include"PlayerJampCommand.h"

class PlayerCommandHandler
{
public:
	PlayerCommandHandler() {};
	~PlayerCommandHandler() {};

	void Handler();

	void CommandExec(Player&p);

private:

	queue<unique_ptr<IPlayerCommand>>commands_;

};