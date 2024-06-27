#include "PlayerShootCommand.h"

void PlayerShootCommand::Exec(Player& p)
{
	p.Shoot();
}
