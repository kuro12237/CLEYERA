#include "PlayerShootCommand.h"

void PlayerShootCommand::Exec(Player& p)
{
	p.Shoot();
}

void PlayerShootCommand::UnExec(Player& p)
{
	p;
}
