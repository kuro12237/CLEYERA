#pragma once
#include"IPlayerCommand.h"
#include"../Player.h"

class PlayerSquatCommand:public IPlayerCommand
{
public:
	PlayerSquatCommand() {};
	~PlayerSquatCommand() {};

	void Exec(Player& p)override;

	void UnExec(Player& p)override;

private:

};