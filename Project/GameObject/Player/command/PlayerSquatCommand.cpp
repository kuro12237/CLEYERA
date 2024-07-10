#include "PlayerSquatCommand.h"

void PlayerSquatCommand::Exec(Player& p)
{
	p.Squat();
}

void PlayerSquatCommand::UnExec(Player& p)
{
	p.UnSquat();
}
