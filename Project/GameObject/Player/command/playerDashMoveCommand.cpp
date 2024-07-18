#include "playerDashMoveCommand.h"

void PlayerDashMoveCommand::Exec(Player& p)
{
	p.Move(0.2f);
}
