#include "PlayerMoveCommand.h"

void PlayerMoveCommand::Exec(Player& p)
{
	p.Move();
}
