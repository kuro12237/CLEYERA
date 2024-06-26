#pragma once
#include"GameObject/Player/command/IPlayerCommand.h"
#include"GameObject/Player/Player.h"

class PlayerMoveCommand:public IPlayerCommand
{
public:
	PlayerMoveCommand() {};
	~PlayerMoveCommand() {};

	void Exec(Player& p)override;

private:



};

