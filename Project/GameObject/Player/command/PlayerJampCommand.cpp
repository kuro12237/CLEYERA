#include "PlayerJampCommand.h"

void PlayerJampCommand::Exec(Player& p)
{
	p.Jamp();
}

void PlayerJampCommand::UnExec(Player& p)
{
	p;
}
