#pragma once
#include"IPlayerCommand.h"
#include"GameObject/Player/Player.h"

class PlayerJampCommand :public IPlayerCommand
{
public:
	PlayerJampCommand() {};
	~PlayerJampCommand() {};

	void Exec(Player& p)override;

private:

};

