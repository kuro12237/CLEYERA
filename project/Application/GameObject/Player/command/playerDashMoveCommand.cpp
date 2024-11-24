#include "playerDashMoveCommand.h"

void PlayerDashMoveCommand::Exec(Player& p)
{
	p.Dash();
}
