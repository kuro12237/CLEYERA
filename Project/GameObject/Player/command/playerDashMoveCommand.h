#pragma once
#include"GameObject/Player/command/IPlayerCommand.h"
#include"GameObject/Player/Player.h"

class PlayerDashMoveCommand :public IPlayerCommand
{
public:
	PlayerDashMoveCommand() {};
	~PlayerDashMoveCommand() {};

	void Exec(Player& p)override;

private:



};