#include "PlayerMoveCommand.h"

void PlayerMoveCommand::Exec(Player& p)
{
	p.Move();
}

void PlayerMoveCommand::UnExec(Player& p)
{
	p;
}
