#pragma once
#include"IPlayerCommand.h"

class PlayerJampCommand:public IPlayerCommand
{
public:
	PlayerJampCommand() {};
	~PlayerJampCommand() {};

	void Exec(Player& player)override;

private:

};
