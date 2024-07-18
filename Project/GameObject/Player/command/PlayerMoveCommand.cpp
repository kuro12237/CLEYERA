#include "PlayerMoveCommand.h"

void PlayerMoveCommand::Exec(Player& p)
{
	const float speed = 0.25f;
	p.Move(speed);
}
